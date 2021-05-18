#include "compiler/BasicBlock.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "parser/ASTNode.h"

namespace LL2W {
	Instruction::~Instruction() {}

	bool Instruction::operator<(const Instruction &other) const {
		return index < other.index;
	}

	bool Instruction::operator>(const Instruction &other) const {
		return index > other.index;
	}

	std::string Instruction::toString() const {
		return "\e[91m<invalid>\e[39m: " + const_cast<Instruction *>(this)->debugExtra();
	}

	std::shared_ptr<Variable> Instruction::doesRead(std::shared_ptr<Variable> var) const {
		if (read.count(var) != 0)
			return var;
		std::shared_ptr<BasicBlock> block = parent.lock();
		for (const VariablePtr &read_var: read)
			if (read_var->id == var->id)
				return read_var;
		for (Variable *alias: var->getAliases()) {
			std::shared_ptr<Variable> shared_alias = block->parent->getVariable(alias->id);
			if (read.count(shared_alias) != 0)
				return shared_alias;
		}

		return nullptr;
	}

	std::shared_ptr<Variable> Instruction::doesWrite(std::shared_ptr<Variable> var) const {
		if (written.count(var) != 0)
			return var;
		std::shared_ptr<BasicBlock> block = parent.lock();
		for (const VariablePtr &written_var: written)
			if (written_var->id == var->id)
				return written_var;
		for (Variable *alias: var->getAliases()) {
			std::shared_ptr<Variable> shared_alias = block->parent->getVariable(alias->id);
			if (written.count(shared_alias) != 0)
				return shared_alias;
		}

		return nullptr;
	}

	Instruction * Instruction::setDebug(const ASTNode &node) {
		debugIndex = node.debugIndex;
		return this;
	}

	Instruction * Instruction::setDebug(const ASTNode *node) {
		debugIndex = node->debugIndex;
		return this;
	}
}
