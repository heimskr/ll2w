#ifndef INSTRUCTION_SIZEDSTACKPOPINSTRUCTION_H_
#define INSTRUCTION_SIZEDSTACKPOPINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct SizedStackPopInstruction: public RType {
		int size; // in bytes
		SizedStackPopInstruction(std::shared_ptr<Variable> rd_, int size_, int index_);
		SizedStackPopInstruction(std::shared_ptr<Variable> rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
