#include <iostream>

#include "compiler/Function.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Variable.h"
#include "parser/Nodes.h"
#include "util/Util.h"

#define IFLV(x, t) do { if (std::shared_ptr<LocalValue> local_value = std::dynamic_pointer_cast<LocalValue>((x))) \
	readname(local_value, (t)); } while (0)
#define FORV(x...) for (ValuePtr value: {x})
#define CAST(t) const t *cast = dynamic_cast<const t *>(node); if (!cast) break

namespace LL2W {
	LLVMInstruction::~LLVMInstruction() {
		if (ownsNode)
			delete node;
	}

	bool LLVMInstruction::isTerminal() const {
		const NodeType type = node->nodeType();
		return type == NodeType::Ret || type == NodeType::Unreachable;
	}

	ExtractionResult LLVMInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		auto readname = [&](std::shared_ptr<LocalValue> lv, TypePtr type) {
			read.insert(parent.lock()->parent->getVariable(Util::parseLong(lv->name), type));
		};

		auto write = [&](const std::string *str, TypePtr type) {
			if (str)
				written.insert(parent.lock()->parent->getVariable(Util::parseLong(str), type, parent.lock()));
		};

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
				std::shared_ptr<PointerType> ptr = std::make_shared<PointerType>(cast->type->copy());
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
				write(cast->result, cast->type);
				FORV(cast->value1, cast->value2)
					IFLV(value, cast->type);
				break;
			}

			case NodeType::BrUncond: {
				// Unconditional branches don't read anything; their PVARs represent labels, not registers.
				break;
			}

			case NodeType::BrCond: {
				CAST(BrCondNode);
				IFLV(cast->condition, std::make_shared<IntType>(1));
				break;
			}

			case NodeType::Call:
			case NodeType::Invoke: {
				CAST(CallInvokeNode);
				write(cast->result, cast->returnType);
				for (ConstantPtr constant: cast->constants)
					IFLV(constant->value, constant->type);
				break;
			}

			case NodeType::Getelementptr: {
				CAST(GetelementptrNode);
				write(cast->result, cast->type);
				if (auto *local = dynamic_cast<LocalValue *>(cast->ptrValue.get()))
					read.insert(parent.lock()->parent->getVariable(Util::parseLong(local->name), cast->ptrType));
				for (auto [width, value, minrange, pvar]: cast->indices) {
					// Because we're assuming that these variables have already been defined earlier in the function,
					// we can get them from the Function that contains this Instruction.
					if (pvar)
						read.insert(parent.lock()->parent->getVariable(value));
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
			case NodeType::Logic:
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

			case NodeType::Unreachable: {
				break;
			}

			default:
				return {-1, -1};
		}

		return {read.size(), written.size()};
	}

	std::string LLVMInstruction::debugExtra() {
		return node->debugExtra();
	}

	std::string LLVMInstruction::toString() const {
		return "\e[41;37;1mUntranslated node:\e[0m " + node->debugExtra();
	}

	bool LLVMInstruction::replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) {
		if (Reader *reader = dynamic_cast<Reader *>(node)) {
			reader->replaceRead(to_replace, new_var);
			return true;
		}

		return false;
	}

	bool LLVMInstruction::isPhi() const {
		return node && node->nodeType() == NodeType::Phi;
	}
}
