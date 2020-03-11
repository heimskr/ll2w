#ifndef INSTRUCTION_LOADIINSTRUCTION_H_
#define INSTRUCTION_LOADIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct LoadIInstruction: public IType<int> {
		using IType::IType;			
		std::string debugExtra() override;
	};
}

#endif
