#include "compiler/Instruction.h"

namespace LL2W {
	Instruction::~Instruction() {}

	bool Instruction::operator<(const Instruction &other) const {
		return index < other.index;
	}

	bool Instruction::operator>(const Instruction &other) const {
		return index > other.index;
	}
}
