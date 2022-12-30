#include "compiler/Variable.h"
#include "instruction/LoadIInstruction.h"

namespace LL2W {
	LoadIInstruction::LoadIInstruction(ValueType imm_, const std::shared_ptr<Variable> &rd_, int index_):
		IType(nullptr, imm_, rd_, index_) {}

	std::string LoadIInstruction::debugExtra() {
		return "\e[2m[\e[22m" + colorize(imm, *rd, 1) + "\e[2m] ->\e[22m " + std::string(*rd);
	}

	std::string LoadIInstruction::toString() const {
		return "[" + LL2W::toString(imm, *rd, 1) + "] -> " + rd->toString();
	}
}
