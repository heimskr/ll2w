#ifndef INSTRUCTION_STOREIINSTRUCTION_H_
#define INSTRUCTION_STOREIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * $rs -> [imm]
	 */
	struct StoreIInstruction: public IType<int> {
		/** The size of the store in bytes. */
		int size;

		StoreIInstruction(std::shared_ptr<Variable> rs_, int imm_, int size_, int index_ = -1);

		std::string debugExtra() override;
	};
}

#endif