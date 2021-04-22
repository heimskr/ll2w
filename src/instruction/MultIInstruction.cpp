#include "compiler/Variable.h"
#include "instruction/MultIInstruction.h"

namespace LL2W {
	MultIInstruction::MultIInstruction(std::shared_ptr<Variable> rs_, ValueType imm_, int index_):
		IType(rs_, imm_, nullptr, index_) {}

	std::string MultIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m*\e[0m " + colorize(imm);
	}

	std::string MultIInstruction::toString() const {
		return rs->toString() + " * " + LL2W::toString(imm);
	}
}
