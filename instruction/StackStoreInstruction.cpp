#include "compiler/Variable.h"
#include "instruction/StackStoreInstruction.h"

namespace LL2W {
	std::string StackStoreInstruction::debugExtra() {
		return "\e[1m[store " + std::string(*variable) + " @ " + std::to_string(location.offset) + "]\e[0m";
	}
}