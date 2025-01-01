#include "instruction/PrintPseudoinstruction.h"
#include "parser/StringSet.h"
#include "util/Util.h"

namespace LL2W {
	PrintPseudoinstruction::PrintPseudoinstruction(Immediate imm_):
		IType(nullptr, imm_, nullptr) {}

	PrintPseudoinstruction::PrintPseudoinstruction(const std::string *text_, bool):
		IType(nullptr, 0, nullptr), text(text_) {}

	PrintPseudoinstruction::PrintPseudoinstruction(const std::string &text_):
		PrintPseudoinstruction(StringSet::intern(text_), false) {}

	std::string PrintPseudoinstruction::debugExtra() const {
		return "<\e[36mp\e[39m \"" + (text? *text : colorize(imm, false)) + "\">";
	}

	std::string PrintPseudoinstruction::toString() const {
		return "<p \"" + (text? *text : LL2W::toString(imm, false)) + "\">";
	}

	Instruction * PrintPseudoinstruction::copy() const {
		return new PrintPseudoinstruction(*this);
	}
}
