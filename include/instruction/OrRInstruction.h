#ifndef INSTRUCTION_ORRINSTRUCTION_H_
#define INSTRUCTION_ORRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct OrRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
