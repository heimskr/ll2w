#include "compiler/Variable.h"
#include "instruction/DeferredSourceMoveInstruction.h"

namespace LL2W {
	std::string DeferredSourceMoveInstruction::debugExtra() {
		return std::string(*rs) + "\e[2m[\e[22m" + std::to_string(registerIndex) + "\e[2m]\e[22m \e[2m->\e[22m " +
			std::string(*rd);
	}

	std::string DeferredSourceMoveInstruction::toString() const {
		return rs->toString() + "[" + std::to_string(registerIndex) + "] -> " + rd->toString() + " (deferred; invalid)";
	}
}
