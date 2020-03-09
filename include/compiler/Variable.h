#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <memory>
#include <ostream>
#include <set>

#include "parser/Types.h"
#include "util/WeakCompare.h"

namespace LL2W {
	class Node;
	class BasicBlock;
	class Instruction;

	class Variable {
		private:
			std::list<Instruction *> useOrder;
			std::unordered_set<Variable *> aliases;
			Variable *parent = nullptr;

		public:
			int id;
			Type *type = nullptr;
			std::set<std::shared_ptr<BasicBlock>> definingBlocks;
			std::weak_ptr<Instruction> lastUse;
			std::set<std::shared_ptr<BasicBlock>> usingBlocks;
			std::set<std::weak_ptr<Instruction>, WeakCompare<Instruction>> definitions, uses;
			int reg = -1;

			Variable *spilledFrom = nullptr; // Tentative.
			std::list<Variable *> spilledTo; // Also tentative.

			Variable(int id_, Type *type_ = nullptr,
			         const std::set<std::shared_ptr<BasicBlock>> &defining_blocks = {},
			         const std::set<std::shared_ptr<BasicBlock>> &using_blocks = {});

			~Variable();

			/** Calculates the sum of each use's estimated execution count. */
			int weight() const;

			/** Calculates the variable's spill cost. */
			int spillCost() const;

			/** Sets up this variable so that changes to a different variable will be reflected in this one. */
			void makeAliasOf(Variable &);

			void addDefiner(std::shared_ptr<BasicBlock>);
			void removeDefiner(std::shared_ptr<BasicBlock>);
			void removeDefinition(std::shared_ptr<Instruction>);

			std::shared_ptr<BasicBlock> onlyDefiner() const;
			std::shared_ptr<Instruction> onlyDefinition() const;

			void setID(int);
			void setType(Type *);
			void setDefiningBlocks(const decltype(definingBlocks) &);
			void setDefinitions(const decltype(definitions) &);
			void setUses(const decltype(uses) &);
			void setUsingBlocks(const decltype(usingBlocks) &);
			void setLastUse(decltype(lastUse));
			void setRegister(int);

			operator std::string() const;
			bool operator==(const Variable &) const;
	};

	std::ostream & operator<<(std::ostream &, const LL2W::Variable &);

	using VariablePtr = std::shared_ptr<Variable>;
}


#endif
