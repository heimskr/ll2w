#include "compiler/BasicBlock.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Variable.h"
#include "instruction/MoveInstruction.h"
#include "util/Timer.h"

namespace LL2W {
	BasicBlock::BasicBlock(Label label_, const std::vector<Label> &preds_,
	                       const std::list<InstructionPtr> &instructions_):
		label(label_), preds(preds_), instructions(instructions_) {}

	void BasicBlock::extract(const InstructionPtr &instruction) {
		if (instruction->parent.lock().get() != this)
			warn() << "Instruction's block is " << *instruction->parent.lock()->label << ", not " << *label << ": "
			       << instruction->debugExtra() << '\n';
		instruction->extract();
		for (auto read_var: instruction->read)
			read.insert(read_var);
		for (auto written_var: instruction->written)
			written.insert(written_var);
		if (instruction->isPhi())
			return;
		for (auto read_var: instruction->read)
			nonPhiRead.insert(read_var);
		for (auto written_var: instruction->written)
			nonPhiWritten.insert(written_var);
	}

	std::pair<char, char> BasicBlock::extract(bool force) {
		Timer timer("BasicBlock::extract");

		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		nonPhiWritten.clear();
		nonPhiRead.clear();

		for (InstructionPtr &instruction: instructions)
			extract(instruction);

		return {read.size(), written.size()};
	}

	void BasicBlock::unextract() {
		read.clear();
		written.clear();
		nonPhiWritten.clear();
		nonPhiRead.clear();
		extracted = false;
	}

	void BasicBlock::extractPhi() {
		phiUses.clear();

		if (instructions.empty()) {
			return;
		}

		if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instructions.front().get())) {
			if (PhiNode *phi = dynamic_cast<PhiNode *>(llvm->getNode())) {
				for (const std::pair<ValuePtr, const std::string *> &pair: phi->pairs) {
					if (pair.first->valueType() == ValueType::Local) {
						phiUses.insert(dynamic_cast<LocalValue *>(pair.first.get())->variable);
					}
				}
			}
		}

		// for (InstructionPtr instruction: parent->categories["MovePhi"])
		// 	if (instruction->parent.lock().get() == this)
		// 		if (auto *move = dynamic_cast<MoveInstruction *>(instruction.get())) {
					// std::cerr << "Phi: " << *move->rs << " (" << move->debugExtra() << ")\n";
					// phiUses.insert(move->rs);
				// }
	}

	std::vector<std::shared_ptr<BasicBlock>> BasicBlock::goesTo() const {
		if (instructions.empty())
			return {};
		const auto back = instructions.back();
		if (auto *llvm = dynamic_cast<LLVMInstruction *>(back.get())) {
			const NodeType type = llvm->getNodeType();
			if (type == NodeType::BrUncond) {
				return {parent->getBlock(dynamic_cast<BrUncondNode *>(llvm->getNode())->destination)};
			} else if (type == NodeType::BrCond) {
				const auto *cond = dynamic_cast<BrCondNode *>(llvm->getNode());
				return {parent->getBlock(cond->ifTrue), parent->getBlock(cond->ifFalse)};
			} else if (type == NodeType::Ret) {
				return {};
			} else if (type == NodeType::Switch) {
				std::vector<std::shared_ptr<BasicBlock>> out;
				for (const auto &[type, value, switch_label]: dynamic_cast<SwitchNode *>(llvm->getNode())->table)
					out.push_back(parent->getBlock(switch_label));
				return out;
			} else
				throw std::runtime_error("Unrecognized terminal instruction in BasicBlock::goesTo: " +
					back->debugExtra());
		} else
			throw std::runtime_error("Unrecognized terminal instruction in BasicBlock::goesTo: " + back->debugExtra());
	}

	bool BasicBlock::inPhiDefs(const VariablePtr &var) const {
		bool found_in_written = false;
		for (const VariablePtr &other: written)
			if (*var == *other) {
				found_in_written = true;
				break;
			}
		if (!found_in_written)
			return false;
		for (const VariablePtr &other: nonPhiWritten)
			if (*var == *other)
				return false;
		return true;
	}

	void BasicBlock::insertBeforeTerminal(const InstructionPtr &instruction) {
		instruction->parent = shared_from_this();

		if (instructions.empty()) {
			instructions.push_back(instruction);
		} else {
			auto iter = instructions.end();
			instructions.insert(--iter, instruction);
		}

		extract(instruction);
	}

	bool BasicBlock::isLiveIn(const VariablePtr &var) const {
		if (0 < liveIn.count(var))
			return true;
		for (const VariablePtr &live_in: liveIn)
			if (live_in->id == var->id)
				return true;
		return false;
	}

	bool BasicBlock::isLiveOut(const VariablePtr &var) const {
		if (0 < liveOut.count(var))
			return true;
		for (const VariablePtr &live_out: liveOut)
			if (live_out->id == var->id)
				return true;
		return false;
	}

	std::ostream & operator<<(std::ostream &os, const BasicBlock &block) {
		return os << "%" << *block.label;
	}
}
