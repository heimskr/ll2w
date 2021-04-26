#include "compiler/Variable.h"
#include "instruction/SvpgInstruction.h"

namespace LL2W {
	std::string SvpgInstruction::debugExtra() {
		return "\e[36mpage\e[39m \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SvpgInstruction::toString() const {
		return "page -> " + rd->toString();
	}
}
