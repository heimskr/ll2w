#ifndef INSTRUCTION_SUBIINSTRUCTION_H_
#define INSTRUCTION_SUBIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct SubIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
