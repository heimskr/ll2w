#include "compiler/Variable.h"
#include "instruction/OrRInstruction.h"

namespace LL2W {
	std::string OrRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m|\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}
}
