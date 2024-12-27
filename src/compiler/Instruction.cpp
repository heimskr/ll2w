#include "compiler/BasicBlock.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "parser/ASTNode.h"

#include <llvm/IR/Instructions.h>

namespace LL2W {
	bool Instruction::operator<(const Instruction &other) const {
		return index < other.index;
	}

	bool Instruction::operator>(const Instruction &other) const {
		return index > other.index;
	}

	std::string Instruction::toString() const {
		return "\e[91m<invalid>\e[39m: " + const_cast<Instruction *>(this)->debugExtra();
	}

	VariablePtr Instruction::doesRead(const VariablePtr &var) const {
		if (read.contains(var)) {
			return var;
		}

		BasicBlockPtr block = parent.lock();

		for (const VariablePtr &read_var: read) {
			if (read_var->id == var->id) {
				return read_var;
			}
		}

		for (Variable *alias: var->getAliases()) {
			VariablePtr shared_alias = block->parent->getVariable(alias->id);
			if (read.contains(shared_alias)) {
				return shared_alias;
			}
		}

		return nullptr;
	}

	VariablePtr Instruction::doesWrite(const VariablePtr &var) const {
		if (written.contains(var)) {
			return var;
		}

		BasicBlockPtr block = parent.lock();

		for (const VariablePtr &written_var: written) {
			if (written_var->id == var->id) {
				return written_var;
			}
		}

		for (Variable *alias: var->getAliases()) {
			VariablePtr shared_alias = block->parent->getVariable(alias->id);
			if (written.contains(shared_alias)) {
				return shared_alias;
			}
		}

		return nullptr;
	}

	Instruction * Instruction::setDebug(const ASTNode &node) {
		return setDebug(node.debugIndex);
	}

	Instruction * Instruction::setDebug(const ASTNode *node) {
		return setDebug(node->debugIndex);
	}

	std::unordered_set<VariablePtr> & Instruction::getRead() {
		return read;
	}

	std::unordered_set<VariablePtr> & Instruction::getWritten() {
		return written;
	}

	int Instruction::getIndex() const {
		return index;
	}

	std::ostream & operator<<(std::ostream &os, const Instruction &instruction) {
		return os << instruction.debugExtra();
	}

	std::ostream & operator<<(std::ostream &os, const InstructionPtr &instruction) {
		return os << instruction->debugExtra();
	}
}
