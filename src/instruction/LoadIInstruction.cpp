#include "compiler/Variable.h"
#include "instruction/LoadIInstruction.h"

namespace LL2W {
	LoadIInstruction::LoadIInstruction(int imm_, std::shared_ptr<Variable> rd_, int size_, int index_):
		IType(nullptr, imm_, rd_, index_), SizedInstruction(size_) {}

	std::string LoadIInstruction::debugExtra() {
		return "\e[2m[\e[0;91m" + std::to_string(imm) + "\e[0;2m] ->\e[0m " + std::string(*rd) + suffix();
	}

	std::string LoadIInstruction::toString() const {
		return "[" + std::to_string(imm) + "] -> " + rd->toString() + suffix();
	}
}
