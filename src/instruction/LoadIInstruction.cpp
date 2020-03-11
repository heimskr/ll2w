#include "compiler/Variable.h"
#include "instruction/LoadIInstruction.h"

namespace LL2W {
	std::string LoadIInstruction::debugExtra() {
		return "\e[2m[\e[0;91m" + std::to_string(imm) + "\e[0;2m] ->\e[0m " + std::string(*rd);
	}
}
