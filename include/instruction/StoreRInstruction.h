#ifndef INSTRUCTION_STORERINSTRUCTION_H_
#define INSTRUCTION_STORERINSTRUCTION_H_

#include "instruction/RType.h"
#include "instruction/SizedInstruction.h"

namespace LL2W {
	/**
	 * $rs -> [$rd]
	 */
	struct StoreRInstruction: public RType, public SizedInstruction {
		/** The size of the store in bytes. */
		int size;

		StoreRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_ = 8, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
