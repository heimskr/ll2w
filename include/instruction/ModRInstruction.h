#ifndef INSTRUCTION_MODRINSTRUCTION_H_
#define INSTRUCTION_MODRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct ModRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
