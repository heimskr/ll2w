#ifndef INSTRUCTION_LOADIINSTRUCTION_H_
#define INSTRUCTION_LOADIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct LoadIInstruction: public IType<int> {
		/** The size of the load in bytes. */
		int size;

		LoadIInstruction(std::shared_ptr<Variable> rs_, int imm_, std::shared_ptr<Variable> rd_, int size_,
		int index_ = -1);

		std::string debugExtra() override;
	};
}

#endif
