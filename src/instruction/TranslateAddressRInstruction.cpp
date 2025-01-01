#include "compiler/Variable.h"
#include "instruction/TranslateAddressRInstruction.h"

namespace LL2W {
	TranslateAddressRInstruction::TranslateAddressRInstruction(VariablePtr rs_, VariablePtr rd_):
		RType(std::move(rs_), nullptr, std::move(rd_)) {}

	std::string TranslateAddressRInstruction::debugExtra() const {
		return "translate " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string TranslateAddressRInstruction::toString() const {
		return "translate " + rs->toString() + " -> " + rd->toString();
	}

	Instruction * TranslateAddressRInstruction::copy() const {
		return new TranslateAddressRInstruction(*this);
	}
}
