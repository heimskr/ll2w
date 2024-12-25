#include "compiler/Variable.h"
#include "instruction/SextRInstruction.h"

#include <format>

namespace LL2W {
	static std::string getMnemonic(const VariablePtr &rs) {
		int width = rs->type->width();
		if (width == 64) { raise(SIGTRAP); }
		return std::format("sext{}", std::max(width, 8));
	}

	SextRInstruction::SextRInstruction(VariablePtr rs, VariablePtr rd):
		LinkedSD(std::move(rs), nullptr, std::move(rd)) {
			if (this->rs->type->width() == 64) { raise(SIGTRAP); }
		}

	std::string SextRInstruction::debugExtra() const {
		return "\e[1m" + getMnemonic(rs) + "\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SextRInstruction::toString() const {
		return getMnemonic(rs) + ' ' + rs->toString() + " -> " + rd->toString();
	}

	Instruction * SextRInstruction::copy() const {
		return new SextRInstruction(*this);
	}
}
