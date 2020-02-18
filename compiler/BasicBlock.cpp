#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"

namespace LL2W {
	BasicBlock::BasicBlock(int label_, const std::vector<int> &preds_,
	                       const std::vector<std::shared_ptr<Instruction>> &instructions_):
		label(label_), preds(preds_), instructions(instructions_) {
		for (std::shared_ptr<Instruction> &instruction: instructions)
			instruction->parent = this;
	}

	std::pair<char, char> BasicBlock::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();

		for (std::shared_ptr<Instruction> &instruction: instructions) {
			instruction->extract();
			for (auto read_var: instruction->read)
				read.insert(read_var);
			for (auto written_var: instruction->written)
				written.insert(written_var);
		}

		return {read.size(), written.size()};
	}
}
