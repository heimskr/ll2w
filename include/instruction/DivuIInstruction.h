#ifndef INSTRUCTION_DIVUIINSTRUCTION_H_
#define INSTRUCTION_DIVUIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct DivuIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
