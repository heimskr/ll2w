#pragma once

#include "compiler/LivePoint.h"
#include "parser/Nodes.h"

#include <list>
#include <map>
#include <memory>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

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

	class BasicBlock: public std::enable_shared_from_this<BasicBlock>, public LivePoint {
		public:
			using Label = const std::string *;

		private:
			Label label = nullptr;

			bool extracted = false;
			void extract(const InstructionPtr &);

		public:
			int index = -1;
			std::vector<Label> preds;
			std::vector<Label> succs;
			std::list<InstructionPtr> instructions;
			std::unordered_set<VariablePtr> read;
			std::unordered_set<VariablePtr> written;
			std::unordered_set<VariablePtr> mentioned;
			std::unordered_set<VariablePtr> nonPhiWritten;
			std::unordered_set<VariablePtr> nonPhiRead;
			std::unordered_set<VariablePtr> nonPhiMentioned;
			/** A set of all variables used by ϕ-instructions in this block. */
			std::unordered_set<VariablePtr> phiUses;
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

			void setLabel(Label);
			inline auto getLabel() const { return label; }

			std::string debugExtra() const final;
			std::unordered_set<VariablePtr> & getRead() final;
			std::unordered_set<VariablePtr> & getWritten() final;
			int getIndex() const final;
			std::string getName() const final;
	};

	using BasicBlockPtr = std::shared_ptr<BasicBlock>;
	std::ostream & operator<<(std::ostream &, const BasicBlock &);
}
