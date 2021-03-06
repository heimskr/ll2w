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
			std::weak_ptr<Variable> parent;
			std::optional<int> spillCost_;

		public:
			const int originalID;
			int id;
			TypePtr type = nullptr;
			WeakSet<BasicBlock>  definingBlocks, usingBlocks;
			WeakSet<Instruction> definitions, uses;
			std::weak_ptr<Instruction> lastUse;
			std::set<int> registers;
			std::unordered_set<Variable *> phiParents, phiChildren;

			Variable *spilledFrom = nullptr; // Tentative.
			std::list<Variable *> spilledTo; // Also tentative.

			Variable(int id_, TypePtr type_ = nullptr,
			         const WeakSet<BasicBlock> &defining_blocks = {}, const WeakSet<BasicBlock> &using_blocks = {});

			/** Calculates the sum of each use's estimated execution count. */
			int weight() const;

			/** Calculates the variable's spill cost. */
			int spillCost();
			void clearSpillCost();

			/** Returns whether the variable has only one using block and whose single using block is the same as its
			 *  defining block. */
			bool isSimple() const;

			/** Returns the name of the function in which this variable occurs. */
			std::string functionName() const;

			/** If this variable has a parent, the parent's ID is returned. Otherwise, this variable's ID is returned.
			 */
			int parentID() const;

			/** Sets up this variable so that changes to a different variable will be reflected in this one. */
			void makeAliasOf(std::shared_ptr<Variable>);

			std::weak_ptr<Variable> getParent() const { return parent; }
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

			void setID(int);
			void setType(TypePtr);
			void setDefiningBlocks(const decltype(definingBlocks) &);
			void setDefinitions(const decltype(definitions) &);
			void setUses(const decltype(uses) &);
			void setUsingBlocks(const decltype(usingBlocks) &);
			void setLastUse(decltype(lastUse));
			void setRegisters(const decltype(registers) &);

			/** Returns true if the variable has at least one register that is special purpose. */
			bool hasSpecialRegister() const;
			/** Returns true if the variable has at least one register that isn't special purpose. */
			bool hasNonSpecialRegister() const;
			/** Returns the number of non-special-purpose registers. */
			int nonSpecialCount() const;
			/** Returns true if the variable has at least one register and all registers are special-purpose. */
			bool allRegistersSpecial() const;
			/** Returns true if this variable has the same set of registers as the argument. */
			bool compareRegisters(const Variable &) const;
			/** Returns the number of registers required to contain all the variable's data. Not useful if the variable
			 *  has no type information. */
			int registersRequired(bool may_warn = true) const;
			/** Returns true if the variable has been assigned more than one register. */
			bool multireg() const;
			/** Returns a string containing all the assigned registers.
			 *  The string is of the form "$reg" or "($reg1 $reg2 ...)". */
			std::string registersString() const;

			std::string toString() const;
			std::string plainString() const;
			operator std::string() const;
			bool operator==(const Variable &) const;

			/** Returns whether the variables are same (with operator==) or whether they're both precolored with
			 *  matching register sets. */
			bool equivalent(const Variable &) const;

			void debug();
	};

	std::ostream & operator<<(std::ostream &, const LL2W::Variable &);

	using VariablePtr = std::shared_ptr<Variable>;
}


#endif
