#ifndef INSTRUCTION_DIVUIIINSTRUCTION_H_
#define INSTRUCTION_DIVUIIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct DivuiIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() const override;
		std::string toString() const override;
	};
}

#endif
