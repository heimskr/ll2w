#include "compiler/Variable.h"
#include "instruction/SubIInstruction.h"

namespace LL2W {
	std::string SubIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-\e[0m " + std::to_string(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}
}