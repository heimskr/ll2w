#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <memory>
#include <optional>
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
			std::optional<int> spillCost_;

		public:
			const std::string *id;
			TypePtr type = nullptr;
			WeakSet<BasicBlock>  definingBlocks, usingBlocks;
			WeakSet<Instruction> definitions, uses;
			std::weak_ptr<Instruction> lastUse;
			int reg = -1;

			Variable *spilledFrom = nullptr; // Tentative.
			std::list<Variable *> spilledTo; // Also tentative.

			Variable(const std::string *id_, TypePtr type_ = nullptr,
			         const WeakSet<BasicBlock> &defining_blocks = {}, const WeakSet<BasicBlock> &using_blocks = {});

			/** Calculates the sum of each use's estimated execution count. */
			int weight() const;

			/** Calculates the variable's spill cost. */
			int spillCost();
			void clearSpillCost();

			/** Returns whether the variable has only one using block and whose single using block is the same as its
			 *  defining block. */
			bool isSimple() const;

			/** Sets up this variable so that changes to a different variable will be reflected in this one. */
			void makeAliasOf(Variable &);

			const std::unordered_set<Variable *> & getAliases() const { return aliases; }

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

			void setID(const std::string *);
			void setType(TypePtr);
			void setDefiningBlocks(const decltype(definingBlocks) &);
			void setDefinitions(const decltype(definitions) &);
			void setUses(const decltype(uses) &);
			void setUsingBlocks(const decltype(usingBlocks) &);
			void setLastUse(decltype(lastUse));
			void setRegister(int);

			std::string toString() const;
			std::string plainString() const;
			operator std::string() const;
			bool operator==(const Variable &) const;

			void debug();
	};

	std::ostream & operator<<(std::ostream &, const LL2W::Variable &);

	using VariablePtr = std::shared_ptr<Variable>;
}


#endif
