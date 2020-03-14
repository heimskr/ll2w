#ifndef INSTRUCTION_INVALIDINSTRUCTION_H_
#define INSTRUCTION_INVALIDINSTRUCTION_H_

#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	struct InvalidInstruction: public IntermediateInstruction {
		InvalidInstruction(int index_ = -1): IntermediateInstruction(index_) {}
		std::string debugExtra() override { return "\e[41;97;1mINVALID\e[39;49;22m"; }
		bool maySpill() const override { return false; }
	};
}

#endif
