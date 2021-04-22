#ifndef INSTRUCTION_SETINSTRUCTION_H_
#define INSTRUCTION_SETINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * imm -> $rd
	 */
	struct SetInstruction: public IType<> {
		SetInstruction(std::shared_ptr<Variable> rd_, ValueType imm_, int index_ = -1):
			IType(nullptr, imm_, rd_, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
