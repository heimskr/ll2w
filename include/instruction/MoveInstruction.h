#ifndef INSTRUCTION_MOVEINSTRUCTION_H_
#define INSTRUCTION_MOVEINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct MoveInstruction: public RType {
		MoveInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int index_ = -1):
			RType(rs_, nullptr, rd_, index_) {}

		std::string debugExtra() override;
	};
}

#endif
