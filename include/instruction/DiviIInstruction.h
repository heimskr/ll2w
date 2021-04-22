#ifndef INSTRUCTION_DIVIIINSTRUCTION_H_
#define INSTRUCTION_DIVIIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct DiviIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
