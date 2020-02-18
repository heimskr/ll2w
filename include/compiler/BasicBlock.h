#ifndef COMPILER_BASICBLOCK_H_
#define COMPILER_BASICBLOCK_H_

#include <map>
#include <memory>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

#include "parser/Nodes.h"

namespace LL2W {
	class Instruction;
	class Variable;
	class Node;
	class Function;
	class LLVMInstruction;
	class Type;

	class BasicBlock {
		private:
			bool extracted = false;

		public:
			int label;
			std::vector<int> preds;
			std::vector<std::shared_ptr<Instruction>> instructions;
			std::set<std::shared_ptr<Variable>> read, written;
			std::unordered_set<std::shared_ptr<Variable>> liveIn, liveOut;
			Node *node;
			Function *parent = nullptr;
			/** The total number of instructions in all basic blocks preceding this one. */
			int offset = -1;
			int estimatedExecutions = 0;

			BasicBlock(int, const std::vector<int> &, const std::vector<std::shared_ptr<Instruction>> &);

			std::pair<char, char> extract(bool force = false);

			size_t size() const { return instructions.size(); }
	};

	using BasicBlockPtr = std::shared_ptr<BasicBlock>;
}

#endif
