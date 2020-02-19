#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <memory>
#include <set>

#include "parser/Types.h"

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
			Instruction *lastUse = nullptr;
			std::set<std::shared_ptr<BasicBlock>> usingBlocks;
			std::set<Instruction *> definitions, uses;
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

			std::shared_ptr<BasicBlock> onlyDefinition() const;

			void setID(int);
			void setType(Type *);
			void setDefiningBlocks(const std::set<std::shared_ptr<BasicBlock>> &);
			void setDefinitions(const std::set<Instruction *> &);
			void setUses(const std::set<Instruction *> &);
			void setUsingBlocks(const std::set<std::shared_ptr<BasicBlock>> &);
			void setLastUse(Instruction *);
			void setRegister(int);

			bool operator==(const Variable &) const;
	};

	using VariablePtr = std::shared_ptr<Variable>;
}

#endif
