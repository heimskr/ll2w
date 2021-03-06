#pragma once

#include "instruction/IType.h"
#include "instruction/SizedInstruction.h"

namespace LL2W {
	/**
	 * [imm] -> $rd
	 */
	struct LoadIInstruction: public IType<>, public SizedInstruction {
		LoadIInstruction(ValueType imm_, std::shared_ptr<Variable> rd_, int size_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
