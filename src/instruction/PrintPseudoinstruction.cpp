#include "instruction/PrintPseudoinstruction.h"

namespace LL2W {
	PrintPseudoinstruction::PrintPseudoinstruction(ValueType imm_, int index_):
		IType(nullptr, imm_, nullptr, index_) {}

	std::string PrintPseudoinstruction::debugExtra() {
		return "<\e[36mp\e[39m " + colorize(imm, false) + ">";
	}

	std::string PrintPseudoinstruction::toString() const {
		return "<p " + LL2W::toString(imm, false) + ">";
	}
}
