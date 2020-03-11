#ifndef INSTRUCTION_ADDRINSTRUCTION_H_
#define INSTRUCTION_ADDRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct AddRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
	};
}

#endif
