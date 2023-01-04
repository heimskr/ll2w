#include "compiler/Variable.h"
#include "instruction/TranslateAddressRInstruction.h"

namespace LL2W {
	TranslateAddressRInstruction::TranslateAddressRInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		RType(std::move(rs_), nullptr, std::move(rd_), index_) {}

	std::string TranslateAddressRInstruction::debugExtra() {
		return "translate " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string TranslateAddressRInstruction::toString() const {
		return "translate " + rs->toString() + " -> " + rd->toString();
	}
}
