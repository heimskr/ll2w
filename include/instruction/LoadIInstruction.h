#ifndef INSTRUCTION_LOADIINSTRUCTION_H_
#define INSTRUCTION_LOADIINSTRUCTION_H_

#include "instruction/IType.h"
#include "instruction/SizedInstruction.h"

namespace LL2W {
	/**
	 * [imm] -> $rd
	 */
	struct LoadIInstruction: public IType<int>, public SizedInstruction {
		/** The size of the load in bytes. */
		int size;

		LoadIInstruction(int imm_, std::shared_ptr<Variable> rd_, int size_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
