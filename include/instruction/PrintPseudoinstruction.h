#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct PrintPseudoinstruction: IType<> {
		const std::string *text = nullptr;
		PrintPseudoinstruction(ValueType imm_, int index_ = -1);
		PrintPseudoinstruction(const std::string *text_, bool dummy, int index = -1);
		PrintPseudoinstruction(const std::string &text_, int index = -1);
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}