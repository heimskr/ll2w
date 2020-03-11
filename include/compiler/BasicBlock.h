#ifndef COMPILER_BASICBLOCK_H_
#define COMPILER_BASICBLOCK_H_

#include <list>
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
			void extract(Instruction &);

		public:
			int label;
			int index = -1;
			std::vector<int> preds;
			std::list<std::shared_ptr<Instruction>> instructions;
			std::set<std::shared_ptr<Variable>> read, written;
			std::unordered_set<std::shared_ptr<Variable>> liveIn, liveOut;
			Node *node = nullptr;
			Function *parent = nullptr;
			/** The total number of instructions in all basic blocks preceding this one. */
			int offset = -1;
			int estimatedExecutions = 0;

			BasicBlock(int, const std::vector<int> &, const std::list<std::shared_ptr<Instruction>> &);

			std::pair<char, char> extract(bool force = false);
			void unextract();

			size_t size() const { return instructions.size(); }

			/** Inserts an instruction right before the basic block's terminal instruction.
			 *  This function assumes that every basic block has exactly one terminal instruction. */
			void insertBeforeTerminal(std::shared_ptr<Instruction>);

			int countDefinitions();

			bool isLiveIn(std::shared_ptr<Variable>) const;
			bool isLiveOut(std::shared_ptr<Variable>) const;
	};

	using BasicBlockPtr = std::shared_ptr<BasicBlock>;
}

#endif
