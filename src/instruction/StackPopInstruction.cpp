#include "compiler/Variable.h"
#include "instruction/StackPopInstruction.h"

namespace LL2W {
	StackPopInstruction::StackPopInstruction(std::shared_ptr<Variable> rd_, int index_):
		RType(nullptr, nullptr, rd_, index_) {}

	std::string StackPopInstruction::debugExtra() {
		return "\e[2m]\e[22m " + std::string(*rd);
	}

	std::string StackPopInstruction::toString() const {
		return "] " + rd->toString();
	}
}
