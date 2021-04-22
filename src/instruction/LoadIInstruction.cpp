#include "compiler/Variable.h"
#include "instruction/LoadIInstruction.h"

namespace LL2W {
	LoadIInstruction::LoadIInstruction(ValueType imm_, std::shared_ptr<Variable> rd_, int size_, int index_):
		IType(nullptr, imm_, rd_, index_), SizedInstruction(size_) {}

	std::string LoadIInstruction::debugExtra() {
		return "\e[2m[\e[22m" + colorize(imm) + "\e[2m] ->\e[22m " + std::string(*rd) + suffix();
	}

	std::string LoadIInstruction::toString() const {
		return "[" + LL2W::toString(imm) + "] -> " + rd->toString() + suffix();
	}
}
