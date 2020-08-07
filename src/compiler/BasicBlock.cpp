#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Variable.h"

namespace LL2W {
	BasicBlock::BasicBlock(const std::string *label_, const std::vector<const std::string *> &preds_,
	                       const std::list<std::shared_ptr<Instruction>> &instructions_):
		label(label_), preds(preds_), instructions(instructions_) {}

	void BasicBlock::extract(std::shared_ptr<Instruction> &instruction) {
		instruction->extract();
		for (auto read_var: instruction->read)
			read.insert(read_var);
		for (auto written_var: instruction->written)
			written.insert(written_var);
		if (instruction->isPhi()) {
			phiNode = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			return;
		}
		for (auto read_var: instruction->read)
			nonPhiRead.insert(read_var);
		for (auto written_var: instruction->written)
			nonPhiWritten.insert(written_var);
	}

	std::pair<char, char> BasicBlock::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		nonPhiWritten.clear();
		nonPhiRead.clear();

		for (std::shared_ptr<Instruction> &instruction: instructions)
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

		if (instructions.empty())
			return;

		if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instructions.front().get()))
			if (PhiNode *phi = dynamic_cast<PhiNode *>(llvm->node))
				for (const std::pair<ValuePtr, const std::string *> &pair: phi->pairs)
					if (pair.first->valueType() == ValueType::Local)
						phiUses.insert(dynamic_cast<LocalValue *>(pair.first.get())->variable);
	}

	bool BasicBlock::inPhiDefs(std::shared_ptr<Variable> var) const {
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

	void BasicBlock::insertBeforeTerminal(std::shared_ptr<Instruction> instruction) {
		if (instructions.empty()) {
			instructions.push_back(instruction);
		} else {
			auto iter = instructions.end();
			instructions.insert(--iter, instruction);
		}

		extract(instruction);
	}

	bool BasicBlock::isLiveIn(std::shared_ptr<Variable> var) const {
		if (0 < liveIn.count(var))
			return true;
		for (const std::shared_ptr<Variable> &live_in: liveIn)
			if (live_in->id == var->id)
				return true;
		return false;
	}

	bool BasicBlock::isLiveOut(std::shared_ptr<Variable> var) const {
		if (0 < liveOut.count(var))
			return true;
		for (const std::shared_ptr<Variable> &live_out: liveOut)
			if (live_out->id == var->id)
				return true;
		return false;
	}

	std::ostream & operator<<(std::ostream &os, const BasicBlock &block) {
		return os << "%" << *block.label;
	}
}
