#ifndef INSTRUCTION_ORIINSTRUCTION_H_
#define INSTRUCTION_ORIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct OrIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
	};
}

#endif
