#include "compiler/Variable.h"
#include "instruction/MemsetInstruction.h"

namespace LL2W {
	std::string MemsetInstruction::debugExtra() {
		return "\e[36mmemset\e[39m " + std::string(*rs) + " x " + std::string(*rt) + " \e[2m->\e[22m "
		       + std::string(*rd);
	}

	std::string MemsetInstruction::toString() const {
		return "memset " + rs->toString() + " x " + rt->toString() + " -> " + rd->toString();
	}
}
