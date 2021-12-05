#include "compiler/Variable.h"
#include "instruction/TranslateAddressRInstruction.h"

namespace LL2W {
	std::string TranslateAddressRInstruction::debugExtra() {
		return "translate " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string TranslateAddressRInstruction::toString() const {
		return "translate " + rs->toString() + " -> " + rd->toString();
	}
}
