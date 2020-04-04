#ifndef INSTRUCTION_XORIINSTRUCTION_H_
#define INSTRUCTION_XORIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct XorIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
	};
}

#endif
