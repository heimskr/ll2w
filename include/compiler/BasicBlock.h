#ifndef COMPILER_BASICBLOCK_H_
#define COMPILER_BASICBLOCK_H_

#include <vector>

#include "parser/Nodes.h"

namespace LL2W {
	class BasicBlock {
		public:
			int index;
			std::vector<int> preds;
			std::vector<const InstructionNode *> instructions;
			BasicBlock(int, const std::vector<int> &, const std::vector<const InstructionNode *> &);
	};
}

#endif
