#ifndef INSTRUCTION_LOADRINSTRUCTION_H_
#define INSTRUCTION_LOADRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	/**
	 * [$rs] -> $rd
	 */
	struct LoadRInstruction: public RType {
		/** The size of the load in bytes. */
		int size;

		LoadRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_ = 8, int index_ = -1);

		std::string debugExtra() override;
	};
}

#endif
