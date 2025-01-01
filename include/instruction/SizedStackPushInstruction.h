#ifndef INSTRUCTION_SIZEDSTACKPUSHINSTRUCTION_H_
#define INSTRUCTION_SIZEDSTACKPUSHINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct SizedStackPushInstruction: public RType {
		int size; // in bytes
		SizedStackPushInstruction(std::shared_ptr<Variable> rs_, int size_, int index_);
		SizedStackPushInstruction(std::shared_ptr<Variable> rs_);
		std::string debugExtra() const override;
		std::string toString() const override;
	};
}

#endif
