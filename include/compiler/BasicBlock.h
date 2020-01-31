#ifndef COMPILER_BASICBLOCK_H_
#define COMPILER_BASICBLOCK_H_

#include <memory>
#include <vector>

#include "parser/Nodes.h"

namespace LL2W {
	class Instruction;

	class BasicBlock {
		public:
			int label;
			std::vector<int> preds;
			std::vector<std::shared_ptr<Instruction>> instructions;

			BasicBlock(int, const std::vector<int> &, const std::vector<std::shared_ptr<Instruction>> &);
	};
}

#endif
