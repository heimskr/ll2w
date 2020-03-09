#include "compiler/Variable.h"
#include "instruction/StackStoreInstruction.h"

namespace LL2W {
	std::string StackStoreInstruction::debugExtra() {
		return "[[store " + std::string(*variable) + " @ " + std::to_string(location.offset) + "]]";
	}
}