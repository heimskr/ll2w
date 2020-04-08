#ifndef INSTRUCTIONS_JUMPREGISTERINSTRUCTION_H_
#define INSTRUCTIONS_JUMPREGISTERINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct JumpRegisterInstruction: public RType {
		bool link;

		JumpRegisterInstruction(std::shared_ptr<Variable> rd_, bool link_ = false, int index_ = -1):
			RType(nullptr, nullptr, rd_, index_), link(link_) {}

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
