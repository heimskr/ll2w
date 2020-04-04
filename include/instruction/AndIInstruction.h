#ifndef INSTRUCTION_ANDIINSTRUCTION_H_
#define INSTRUCTION_ANDIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct AndIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
	};
}

#endif
