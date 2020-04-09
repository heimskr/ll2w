#include "compiler/Variable.h"
#include "instruction/LoadRInstruction.h"

namespace LL2W {
	LoadRInstruction::LoadRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_,
	int index_):
		RType(rs_, nullptr, rd_, index_), SizedInstruction(size_) {}

	std::string LoadRInstruction::debugExtra() {
		return "\e[2m[\e[0;91m" + std::string(*rs) + "\e[0;2m] ->\e[0m " + std::string(*rd) + suffix();
	}

	std::string LoadRInstruction::toString() const {
		return "[" + rs->toString() + "] -> " + rd->toString() + suffix();
	}
}
