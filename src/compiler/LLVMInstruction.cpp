#include "compiler/Function.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Variable.h"
#include "parser/Nodes.h"
#include "util/Util.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_os_ostream.h>

#include <iostream>

/** If the first argument is castable to a LocalValue, this macro calls readname with the LocalValue and the provided
 *  type. */
#define IFLV(x, t) do { if (auto local_value = std::dynamic_pointer_cast<LocalValue>((x))) \
	readname(local_value, (t)); } while (0)
#define FORV(x...) for (const auto &value: {x})
#define CAST(t) auto *cast = dynamic_cast<t *>(getNode()); if (!cast) break

namespace LL2W {
	LLVMInstruction::LLVMInstruction(InstructionNode *source, int index, bool owns_node):
		Instruction(index),
		source(source),
		ownsNode(owns_node) {
			if (source != nullptr) {
				debugIndex = source->debugIndex;
			}
		}

	LLVMInstruction::LLVMInstruction(llvm::Instruction *source, int index):
		Instruction(index),
		source(source),
		ownsNode(false) {}

	LLVMInstruction::~LLVMInstruction() {
		if (ownsNode && std::holds_alternative<InstructionNode *>(source)) {
			delete std::get<InstructionNode *>(source);
		}
	}

	bool LLVMInstruction::isTerminal() const {
		const NodeType type = getNodeType();
		return type == NodeType::Ret || type == NodeType::Unreachable;
	}

	ExtractionResult LLVMInstruction::extract(bool force) {
		if (extracted && !force) {
			return {read.size(), written.size()};
		}

		read.clear();
		written.clear();
		extracted = true;

		auto readname = [&](const std::shared_ptr<LocalValue> &lv, const TypePtr &type) {
			if (!secretReads) {
				read.insert(parent.lock()->parent->getVariable(lv->name, type));
			}
		};

		auto write = [&](const std::string *str, const TypePtr &type) {
			if (str != nullptr && !secretWrites) {
				written.insert(parent.lock()->parent->getVariable(str, type, parent.lock()));
			}
		};

		auto *node = getNode();

		switch (node->nodeType()) {
			case NodeType::Select: {
				CAST(SelectNode);
				write(cast->result, cast->firstType);
				IFLV(cast->firstValue, cast->firstType);
				IFLV(cast->secondValue, cast->secondType);
				break;
			}

			case NodeType::Alloca: {
				CAST(AllocaNode);
				auto ptr = std::make_shared<PointerType>(cast->type->copy());
				write(cast->result, ptr);
				IFLV(cast->numelementsValue, cast->numelementsType);
				break;
			}

			case NodeType::Store: {
				CAST(StoreNode);
				// TODO: what if source is a conversion?
				IFLV(cast->source->value, cast->source->type);
				IFLV(cast->destination->value, cast->destination->type);
				break;
			}

			case NodeType::Load: {
				CAST(LoadNode);
				write(cast->result, cast->type);
				IFLV(cast->constant->value, cast->constant->type);
				break;
			}

			case NodeType::Icmp: {
				CAST(IcmpNode);
				write(cast->result, cast->getType());
				for (ValuePtr *value: cast->allValuePointers()) {
					IFLV(*value, cast->getType());
				}
				break;
			}

			case NodeType::Logic: {
				CAST(LogicNode);
				write(cast->result, cast->getType());
				for (ValuePtr *value: cast->allValuePointers()) {
					IFLV(*value, cast->getType());
				}
				break;
			}

			case NodeType::BrUncond: {
				// Unconditional branches don't read anything; their PVARs represent labels, not registers.
				break;
			}

			case NodeType::BrCond: {
				CAST(BrCondNode);
				IFLV(cast->condition->value, IntType::make(8, false));
				break;
			}

			case NodeType::Call:
			case NodeType::Asm:
			case NodeType::Invoke: {
				CAST(CallInvokeNode);
				write(cast->result, cast->returnType);
				IFLV(cast->name, nullptr);
				for (const ConstantPtr &constant: cast->constants) {
					IFLV(constant->value, constant->type);
				}
				break;
			}

			case NodeType::Getelementptr: {
				CAST(GetelementptrNode);
				write(cast->result, std::make_shared<PointerType>(cast->type));
				if (!secretReads) {
					if (auto *local = dynamic_cast<LocalValue *>(cast->allValues().front().get())) {
						read.insert(parent.lock()->parent->getVariable(local->name, cast->constant->convert()->type));
					}
					for (auto [width, value, minrange, pvar]: cast->indices) {
						// Because we're assuming that these variables have already been defined earlier in the
						// function, we can get them from the Function that contains this Instruction.
						if (pvar) {
							read.insert(parent.lock()->parent->getVariable(std::get<Variable::ID>(value), true));
						}
					}
				}
				break;
			}

			case NodeType::Ret: {
				CAST(RetNode);
				IFLV(cast->value, cast->type);
				break;
			}

			case NodeType::Landingpad: {
				CAST(LandingpadNode);
				for (const std::shared_ptr<LandingpadNode::Clause> &clause: cast->clauses)
					IFLV(clause->value, clause->type);
				break;
			}

			case NodeType::Conversion: {
				CAST(ConversionNode);
				write(cast->result, cast->to);
				IFLV(cast->value, cast->from);
				break;
			}

			case NodeType::BasicMath: {
				CAST(BasicMathNode);
				write(cast->result, cast->type);
				FORV(cast->left, cast->right)
					IFLV(value, cast->type);
				break;
			}

			case NodeType::Phi: {
				CAST(PhiNode);
				write(cast->result, cast->type);
				for (const std::pair<ValuePtr, const std::string *> &pair: cast->pairs)
					IFLV(pair.first, cast->type);
				break;
			}

			case NodeType::Div:
			case NodeType::Rem:
			case NodeType::Shr:
			case NodeType::FMath: {
				CAST(SimpleNode);
				write(cast->result, cast->type);
				FORV(cast->left, cast->right)
					IFLV(value, cast->type);
				break;
			}

			case NodeType::ExtractValue: {
				CAST(ExtractValueNode);
				write(cast->result, cast->aggregateType->extractType(cast->decimals));
				IFLV(cast->aggregateValue, cast->aggregateType);
				break;
			}

			case NodeType::InsertValue: {
				CAST(InsertValueNode);
				write(cast->result, cast->aggregateType);
				IFLV(cast->aggregateValue, cast->aggregateType);
				IFLV(cast->value, cast->type);
				break;
			}

			case NodeType::Resume: {
				CAST(ResumeNode);
				IFLV(cast->value, cast->type);
				break;
			}

			case NodeType::Unreachable:
			case NodeType::DbgDeclare:
				break;

			case NodeType::Atomicrmw: {
				CAST(AtomicrmwNode);
				IFLV(cast->value, cast->type);
				IFLV(cast->pointer, cast->pointerType);
				write(cast->result, cast->type);
				break;
			}

			case NodeType::Switch: {
				CAST(SwitchNode);
				IFLV(cast->value, cast->type);
				break;
			}

			case NodeType::Freeze: {
				CAST(FreezeNode);
				IFLV(cast->value, cast->type);
				break;
			}

			default:
				node->debug();
				throw std::runtime_error("Unhandled LLVM instruction");
		}

		return {read.size(), written.size()};
	}

	std::string LLVMInstruction::debugExtra() const {
		if (!isFromLLVM()) {
			return getNode()->debugExtra();
		}

		std::string out;
		llvm::raw_string_ostream os(out);
		getLLVM()->print(os);
		return out;
	}

	std::string LLVMInstruction::toString() const {
		auto *node = getNode();
		return "\e[41;37;1mUntranslated node:\e[0m " + node->debugExtra();
	}

	bool LLVMInstruction::replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) {
		auto *node = getNode();

		if (auto *reader = dynamic_cast<Reader *>(node)) {
			reader->replaceRead(to_replace, new_var);
			return true;
		}

		return false;
	}

	bool LLVMInstruction::canReplaceRead(const VariablePtr &) const {
		auto *node = getNode();
		return dynamic_cast<Reader *>(node) != nullptr;
	}

	bool LLVMInstruction::replaceWritten(const VariablePtr &to_replace, const VariablePtr &new_var) {
		auto *node = getNode();
		if (auto *writer = dynamic_cast<Writer *>(node)) {
			writer->replaceWritten(to_replace, new_var);
			return true;
		}

		return false;
	}

	bool LLVMInstruction::canReplaceWritten(const VariablePtr &) const {
		auto *node = getNode();
		return dynamic_cast<Writer *>(node) != nullptr;
	}

	bool LLVMInstruction::isPhi() const {
		auto *node = getNode();
		return node && node->nodeType() == NodeType::Phi;
	}

	bool LLVMInstruction::holdsLabels() const {
		auto *node = getNode();
		switch (node->nodeType()) {
			case NodeType::BrCond:
			case NodeType::BrUncond:
			case NodeType::Switch:
				return true;
			default:
				return false;
		}
	}

	bool LLVMInstruction::replaceLabel(const std::string *to_replace, const std::string *replace_with) {
		auto *node = getNode();
		switch (node->nodeType()) {
			case NodeType::BrCond: {
				CAST(BrCondNode);
				bool changed = false;
				if (cast->ifFalse == to_replace) {
					cast->ifFalse = replace_with;
					changed = true;
				}
				if (cast->ifTrue == to_replace) {
					cast->ifTrue = replace_with;
					changed = true;
				}
				return changed;
			}

			case NodeType::BrUncond: {
				CAST(BrUncondNode);
				if (cast->destination == to_replace) {
					cast->destination = replace_with;
					return true;
				}
				return false;
			}

			case NodeType::Switch: {
				CAST(SwitchNode);
				bool changed = false;
				if (cast->label == to_replace) {
					cast->label = replace_with;
					changed = true;
				}
				for (auto &[type, value, label]: cast->table)
					if (label == to_replace) {
						label = replace_with;
						changed = true;
					}
				return changed;
			}

			default:;
		}

		return false;
	}

	std::vector<const std::string *> LLVMInstruction::getLabels() const {
		if (isFromLLVM()) {
			auto *instruction = getLLVM();
			if (auto *branch = llvm::dyn_cast<llvm::BranchInst>(instruction)) {
				if (branch->isConditional()) {
					llvm::Value *if_true = branch->getOperand(1);
					llvm::Value *if_false = branch->getOperand(2);
					// TODO
				} else {
					llvm::Value *destination = branch->getOperand(0);
					// TODO
				}
			}

			return {};
		}

		switch (getNodeType()) {
			case NodeType::BrCond: {
				CAST(BrCondNode);
				return {cast->ifFalse, cast->ifTrue};
			}

			case NodeType::BrUncond: {
				CAST(BrUncondNode);
				return {cast->destination};
			}

			case NodeType::Switch: {
				CAST(SwitchNode);
				std::vector<const std::string *> out {cast->label};
				out.reserve(1 + cast->table.size());
				for (const auto &[type, value, label]: cast->table)
					out.push_back(label);
				return out;
			}

			default:;
		}

		return {};
	}

	bool LLVMInstruction::isBlockTerminal() const {
		switch (getNodeType()) {
			case NodeType::BrCond:
			case NodeType::BrUncond:
			case NodeType::Switch:
			case NodeType::Ret:
			case NodeType::Unreachable:
				return true;
			default:
				return false;
		}
	}

	Instruction * LLVMInstruction::copy() const {
		auto out = std::make_unique<LLVMInstruction>(*this);
		if (std::holds_alternative<InstructionNode *>(source)) {
			Util::copyPointer(std::get<InstructionNode *>(out->source));
		}
		return out.release();
	}

	InstructionNode * LLVMInstruction::getNode() const {
		if (!std::holds_alternative<InstructionNode *>(source)) {
			throw std::runtime_error("getNode() failed: not holding an InstructionNode");
		}
		return std::get<InstructionNode *>(source);
	}

	llvm::Instruction * LLVMInstruction::getLLVM() const {
		if (!std::holds_alternative<llvm::Instruction *>(source)) {
			throw std::runtime_error("getLLVM() failed: not holding an llvm::Instruction");
		}
		return std::get<llvm::Instruction *>(source);
	}

	bool LLVMInstruction::isFromLLVM() const {
		return std::holds_alternative<llvm::Instruction *>(source);
	}

	NodeType LLVMInstruction::getNodeType() const {
		if (!isFromLLVM()) {
			return getNode()->nodeType();
		}

		llvm::Instruction *llvm = getLLVM();

		if (auto *branch = llvm::dyn_cast<llvm::BranchInst>(llvm)) {
			return branch->isConditional()? NodeType::BrCond : NodeType::BrUncond;
		}

		if (llvm::isa<llvm::CallInst>(llvm)) {
			return NodeType::Call;
		}

		llvm::raw_os_ostream os(std::cerr);
		llvm->print(os);
		os << "\n";

		throw std::runtime_error("Unknown LLVM instruction type");
	}
}
