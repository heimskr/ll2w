#include "compiler/Variable.h"
#include "instruction/MoveInstruction.h"

namespace LL2W {
	std::string MoveInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string MoveInstruction::toString() const {
		return rs->toString() + " -> " + rd->toString();
	}
}