#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct PrintPseudoinstruction: IType {
		const std::string *text = nullptr;
		PrintPseudoinstruction(Immediate imm_);
		PrintPseudoinstruction(const std::string *text_, bool dummy);
		PrintPseudoinstruction(const std::string &text_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}