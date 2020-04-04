#include "compiler/Variable.h"
#include "instruction/OrIInstruction.h"

namespace LL2W {
	std::string OrIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m|\e[0m " + std::to_string(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}
}
