#include "compiler/Variable.h"
#include "instruction/AddRInstruction.h"

namespace LL2W {
	std::string AddRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m+\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string AddRInstruction::toString() const {
		return rs->toString() + " + " + rt->toString() + " -> " + rd->toString();
	}
}
