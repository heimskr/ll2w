#include "compiler/Variable.h"
#include "instruction/SetptIInstruction.h"

namespace LL2W {
	SetptIInstruction::SetptIInstruction(ValueType imm_, int index_):
		IType(nullptr, std::move(imm_), nullptr, index_) {}

	std::string SetptIInstruction::debugExtra() {
		return "\e[36m%setpt\e[39m " + colorize(imm);
	}

	std::string SetptIInstruction::toString() const {
		return "%setpt " + LL2W::toString(imm);
	}
	
	Instruction * SetptIInstruction::copy() const {
		return new SetptIInstruction(*this);
	}
}
