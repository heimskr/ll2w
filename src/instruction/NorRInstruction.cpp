#include "compiler/Variable.h"
#include "instruction/NorRInstruction.h"

namespace LL2W {
	std::string NorRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m~|\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string NorRInstruction::toString() const {
		return rs->toString() + " ~| " + rt->toString() + " -> " + rd->toString();
	}
}
