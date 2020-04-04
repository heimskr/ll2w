#include "compiler/Variable.h"
#include "instruction/XorIInstruction.h"

namespace LL2W {
	std::string XorIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2mx\e[0m " + std::to_string(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}
}
