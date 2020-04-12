#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <memory>
#include <ostream>
#include <set>
#include <unordered_set>

#include "parser/Types.h"
#include "util/WeakCompare.h"

namespace LL2W {
	class Node;
	class BasicBlock;
	class Instruction;

	class Variable {
		private:
			std::list<Instruction *> useOrder;
			std::set<std::weak_ptr<Variable>, WeakCompare<Variable>> aliases;
			Variable *parent = nullptr;
			std::weak_ptr<Variable> self;

		public:
			int id;
			TypePtr type = nullptr;
			std::unordered_set<std::shared_ptr<BasicBlock>> definingBlocks;
			std::weak_ptr<Instruction> lastUse;
			std::unordered_set<std::shared_ptr<BasicBlock>> usingBlocks;
			std::set<std::weak_ptr<Instruction>, WeakCompare<Instruction>> definitions, uses;
			int reg = -1;

			Variable(int id_, TypePtr type_ = nullptr,
			         const std::unordered_set<std::shared_ptr<BasicBlock>> &defining_blocks = {},
			         const std::unordered_set<std::shared_ptr<BasicBlock>> &using_blocks = {});

			static std::shared_ptr<Variable> make(int id_, TypePtr type_ = nullptr,
				const std::unordered_set<std::shared_ptr<BasicBlock>> &defining_blocks = {},
				const std::unordered_set<std::shared_ptr<BasicBlock>> &using_blocks = {});

			Variable *spilledFrom = nullptr; // Tentative.
			std::list<Variable *> spilledTo; // Also tentative.

			/** Calculates the sum of each use's estimated execution count. */
			int weight() const;

			/** Calculates the variable's spill cost. */
			int spillCost() const;

			/** Sets up this variable so that changes to a different variable will be reflected in this one. */
			void makeAliasOf(std::shared_ptr<Variable>);

			void addDefiner(std::shared_ptr<BasicBlock>);
			void removeDefiner(std::shared_ptr<BasicBlock>);
			void addUsingBlock(std::shared_ptr<BasicBlock>);
			void removeUsingBlock(std::shared_ptr<BasicBlock>);
			void addDefinition(std::shared_ptr<Instruction>);
			void removeDefinition(std::shared_ptr<Instruction>);
			void addUse(std::shared_ptr<Instruction>);
			void removeUse(std::shared_ptr<Instruction>);

			std::shared_ptr<BasicBlock> onlyDefiner() const;
			std::shared_ptr<Instruction> onlyDefinition() const;

			void setID(int);
			void setType(TypePtr);
			void setDefiningBlocks(const decltype(definingBlocks) &);
			void setDefinitions(const decltype(definitions) &);
			void setUses(const decltype(uses) &);
			void setUsingBlocks(const decltype(usingBlocks) &);
			void setLastUse(decltype(lastUse));
			void setRegister(int);

			std::string toString() const;
			operator std::string() const;
			bool operator==(const Variable &) const;

			void debug();
	};

	std::ostream & operator<<(std::ostream &, const LL2W::Variable &);

	using VariablePtr = std::shared_ptr<Variable>;
}


#endif
