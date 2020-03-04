#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"

namespace LL2W {
	BasicBlock::BasicBlock(int label_, const std::vector<int> &preds_,
	                       const std::list<std::shared_ptr<Instruction>> &instructions_):
		label(label_), preds(preds_), instructions(instructions_) {}

	void BasicBlock::extract(Instruction &instruction) {
		instruction.extract();
		for (auto read_var: instruction.read)
			read.insert(read_var);
		for (auto written_var: instruction.written)
			written.insert(written_var);
	}

	std::pair<char, char> BasicBlock::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();

		for (std::shared_ptr<Instruction> &instruction: instructions)
			extract(*instruction);

		return {read.size(), written.size()};
	}

	void BasicBlock::insertBeforeTerminal(std::shared_ptr<Instruction> instruction) {
		if (instructions.empty()) {
			instructions.push_back(instruction);
		} else {
			auto iter = instructions.end();
			instructions.insert(--iter, instruction);
		}

		extract(*instruction);
	}

	bool BasicBlock::isLiveIn(std::shared_ptr<Variable> var) const {
		if (0 < liveIn.count(var))
			return true;
		for (const std::shared_ptr<Variable> live_in: liveIn) {
			if (live_in->id == var->id)
				return true;
		}
		return false;
	}

	bool BasicBlock::isLiveOut(std::shared_ptr<Variable> var) const {
		if (0 < liveOut.count(var))
			return true;
		for (const std::shared_ptr<Variable> live_out: liveOut) {
			if (live_out->id == var->id)
				return true;
		}
		return false;
	}
}
