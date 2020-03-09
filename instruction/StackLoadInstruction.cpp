#include "compiler/Variable.h"
#include "instruction/StackLoadInstruction.h"

namespace LL2W {
	std::string StackLoadInstruction::debugExtra() {
		return "\e[1m[load " + std::string(*result) + " @ " + std::to_string(location.offset) + "]\e[0m";
	}
}