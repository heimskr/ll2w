#pragma once

#include <list>
#include <map>
#include <memory>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

#include "parser/Nodes.h"

namespace llvm {
	class BasicBlock;
}

namespace LL2W {
	class Instruction;
	class Variable;
	class Node;
	class Function;
	class LLVMInstruction;
	class Type;

	using InstructionPtr = std::shared_ptr<Instruction>;
	using VariablePtr = std::shared_ptr<Variable>;

	class BasicBlock: public std::enable_shared_from_this<BasicBlock> {
		public:
			using Label = const std::string *;
			using LivePtr = std::unordered_set<VariablePtr> BasicBlock::*;

		private:
			Label label = nullptr;

			bool extracted = false;
			void extract(const InstructionPtr &);

		public:
			int index = -1;
			std::vector<Label> preds;
			std::list<InstructionPtr> instructions;
			std::set<VariablePtr> read, written, nonPhiWritten, nonPhiRead;
			std::unordered_set<VariablePtr> liveIn, liveOut;
			/** Contains everything in liveIn and liveOut. */
			std::unordered_set<VariablePtr> allLive;
			/** A set of all variables used by ϕ-instructions in this block. */
			std::unordered_set<VariablePtr> phiUses;
			Node *node = nullptr;
			Function *parent = nullptr;
			/** The total number of instructions in all basic blocks preceding this one. */
			int offset = -1;
			int estimatedExecutions = 0;
			llvm::BasicBlock *llvmBlock = nullptr;

			BasicBlock(Label, std::vector<Label> = {}, std::list<InstructionPtr> = {});

			/** Extracts each instruction in the basic block. Returns a pair containing the total number of reads and
			 *  the total number of writes in the basic block. */
			std::pair<char, char> extract(bool force = false);

			/** Resets the cached read/write counts and marks the block as unextracted. */
			void unextract();

			/** Fills phiUses. */
			void extractPhi();

			std::vector<std::shared_ptr<BasicBlock>> goesTo() const;

			bool inPhiDefs(const VariablePtr &) const;

			/** Returns the number of instructions in the basic block. */
			size_t size() const { return instructions.size(); }

			/** Inserts an instruction right before the basic block's terminal instruction.
			 *  This function assumes that every basic block has exactly one terminal instruction, but this assumption
			 *  is false after lowering of terminal instructions. */
			void insertBeforeTerminal(const InstructionPtr &);

			/** Returns the number of instructions in the basic block that define a variable. */
			int countDefinitions();

			bool isLiveIn(const VariablePtr &) const;
			bool isLiveOut(const VariablePtr &) const;

			void setLabel(Label);
			inline auto getLabel() const { return label; }
	};

	using BasicBlockPtr = std::shared_ptr<BasicBlock>;
	std::ostream & operator<<(std::ostream &, const BasicBlock &);
}
