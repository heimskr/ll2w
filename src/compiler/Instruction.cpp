#include "compiler/Instruction.h"

namespace LL2W {
	Instruction::~Instruction() {}

	bool Instruction::operator<(const Instruction &other) const {
		return index < other.index;
	}

	bool Instruction::operator>(const Instruction &other) const {
		return index > other.index;
	}

	std::string Instruction::toString() const {
		return "\e[91m<invalid>\e[39m";
	}
}
