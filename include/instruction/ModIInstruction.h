#ifndef INSTRUCTION_MODIINSTRUCTION_H_
#define INSTRUCTION_MODIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct ModIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
