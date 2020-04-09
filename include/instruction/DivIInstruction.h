#ifndef INSTRUCTION_DIVIINSTRUCTION_H_
#define INSTRUCTION_DIVIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct DivIInstruction: public IType<int> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
