#include "compiler/Variable.h"
#include "instruction/DeferredDestinationMoveInstruction.h"

namespace LL2W {
	std::string DeferredDestinationMoveInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd) + "\e[2m[\e[22m" + std::to_string(registerIndex)
			+ "\e[2m]\e[22m";
	}

	std::string DeferredDestinationMoveInstruction::toString() const {
		return rs->toString() + " -> " + rd->toString() + "[" + std::to_string(registerIndex) + "] (deferred; invalid)";
	}
}
