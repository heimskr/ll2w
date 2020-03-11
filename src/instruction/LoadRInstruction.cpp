#include "compiler/Variable.h"
#include "instruction/LoadRInstruction.h"

namespace LL2W {
	std::string LoadRInstruction::debugExtra() {
		return "\e[2m[\e[0;91m" + std::string(*rs) + "\e[0;2m] ->\e[0m " + std::string(*rd);
	}
}
