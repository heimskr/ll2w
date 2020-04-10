#ifndef INSTRUCTION_SHIFTRIGHTLOGICALIINSTRUCTION_H_
#define INSTRUCTION_SHIFTRIGHTLOGICALIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct ShiftRightLogicalIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
