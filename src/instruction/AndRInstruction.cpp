#include "compiler/Variable.h"
#include "instruction/AndRInstruction.h"

namespace LL2W {
	std::string AndRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m&\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string AndRInstruction::toString() const {
		return rs->toString() + " & " + rt->toString() + " -> " + rd->toString();
	}
}
