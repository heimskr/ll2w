#ifndef INSTRUCTION_ADDIINSTRUCTION_H_
#define INSTRUCTION_ADDIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct AddIInstruction: public IType<int> {
		using IType::IType;
		std::string debugExtra() override;
	};
}

#endif
