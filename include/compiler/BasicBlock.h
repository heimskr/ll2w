#ifndef COMPILER_BASICBLOCK_H_
#define COMPILER_BASICBLOCK_H_

#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "parser/Nodes.h"

namespace LL2W {
	class Instruction;
	struct Variable;
	class Node;

	class BasicBlock {
		private:
			bool extracted = false;

		public:
			int label;
			std::vector<int> preds;
			std::vector<std::shared_ptr<Instruction>> instructions;
			std::set<int> read, written;
			std::unordered_set<Variable *> liveIn, liveOut;
			Node *node;

			BasicBlock(int, const std::vector<int> &, const std::vector<std::shared_ptr<Instruction>> &);

			std::pair<char, char> extract(bool force = false);
	};
}

#endif
