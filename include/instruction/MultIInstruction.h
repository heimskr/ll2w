#ifndef INSTRUCTION_MULTIINSTRUCTION_H_
#define INSTRUCTION_MULTIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct MultIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
	};
}

#endif
