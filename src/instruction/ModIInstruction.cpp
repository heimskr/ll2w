#include "compiler/Variable.h"
#include "instruction/ModIInstruction.h"

namespace LL2W {
	std::string ModIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m%\e[0m " + std::to_string(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}
}
