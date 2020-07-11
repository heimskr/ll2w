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
			const std::string *label;
			int index = -1;
			std::vector<const std::string *> preds;
			std::list<std::shared_ptr<Instruction>> instructions;
			std::set<std::shared_ptr<Variable>> read, written;
			std::unordered_set<std::shared_ptr<Variable>> liveIn, liveOut;
			/** A list of all variables used by phi instructions in this block. */
			std::unordered_set<std::shared_ptr<Variable>> phiUses;
			Node *node = nullptr;
			Function *parent = nullptr;
			/** The total number of instructions in all basic blocks preceding this one. */
			int offset = -1;
			int estimatedExecutions = 0;

			BasicBlock(const std::string *, const std::vector<const std::string *> &,
			           const std::list<std::shared_ptr<Instruction>> &);

			/** Extracts each instruction in the basic block. Returns a pair containing the total number of reads and
			 *  the total number of writes in the basic block. */
			std::pair<char, char> extract(bool force = false);

			/** Resets the cached read/write counts and marks the block as unextracted. */
			void unextract();

			/** Fills phiUses. */
			void extractPhi();

			/** Returns the number of instructions in the basic block. */
			size_t size() const { return instructions.size(); }

			/** Inserts an instruction right before the basic block's terminal instruction.
			 *  This function assumes that every basic block has exactly one terminal instruction. */
			void insertBeforeTerminal(std::shared_ptr<Instruction>);

			/** Returns the number of instructions in the basic block that define a variable. */
			int countDefinitions();

			bool isLiveIn(std::shared_ptr<Variable>) const;
			bool isLiveOut(std::shared_ptr<Variable>) const;
	};

	using BasicBlockPtr = std::shared_ptr<BasicBlock>;
	std::ostream & operator<<(std::ostream &, const BasicBlock &);
}

#endif
