#ifndef COMPILER_WHYINSTRUCTION_H_
#define COMPILER_WHYINSTRUCTION_H_

#include "compiler/Instruction.h"

namespace LL2W {
	class WhyInstruction: public Instruction {
		bool isTerminal() const override { return false; }
		std::pair<char, char> extract(bool force = false) override { return {0, 0}; }
	}
}

#endif
