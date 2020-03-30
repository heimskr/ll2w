#ifndef INSTRUCTION_STORERINSTRUCTION_H_
#define INSTRUCTION_STORERINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct StoreRInstruction: public RType {
		/** The size of the store in bytes. */
		int size;

		StoreRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_ = 8, int index_ = -1);

		std::string debugExtra() override;
	};
}

#endif
