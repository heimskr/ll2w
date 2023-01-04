#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

#include <memory>
#include <string>

namespace LL2W {
	class BasicBlock;
	class Function;
	class Type;

	/** Copies one register into another, but with a different type. */
	struct BitcastInstruction: LinkedSD<RType>, Makeable<BitcastInstruction> {
		BitcastInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1);
		BitcastInstruction(VariablePtr rs_, Function &, std::shared_ptr<Type>, std::shared_ptr<BasicBlock> = nullptr,
		                   int index_ = -1);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
