#include "compiler/Variable.h"
#include "instruction/MultRInstruction.h"

namespace LL2W {
	std::string MultRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m*\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}
}
