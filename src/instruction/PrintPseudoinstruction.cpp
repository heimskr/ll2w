#include "instruction/PrintPseudoinstruction.h"
#include "parser/StringSet.h"
#include "util/Util.h"

namespace LL2W {
	PrintPseudoinstruction::PrintPseudoinstruction(ValueType imm_, int index_):
		IType(nullptr, imm_, nullptr, index_) {}

	PrintPseudoinstruction::PrintPseudoinstruction(const std::string *text_, bool, int index_):
		IType(nullptr, 0, nullptr, index_), text(text_) {}

	PrintPseudoinstruction::PrintPseudoinstruction(const std::string &text_, int index_):
		PrintPseudoinstruction(StringSet::intern(text_), false, index_) {}

	std::string PrintPseudoinstruction::debugExtra() {
		return "<\e[36mp\e[39m \"" + Util::escape(text? *text : colorize(imm, false)) + "\">";
	}

	std::string PrintPseudoinstruction::toString() const {
		return "<p \"" + Util::escape(text? *text : LL2W::toString(imm, false)) + "\">";
	}
}
