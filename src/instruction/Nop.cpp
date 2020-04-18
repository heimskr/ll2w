#include "compiler/Variable.h"
#include "instruction/Nop.h"

namespace LL2W {
	Nop::Nop(int index_): WhyInstruction(index_) {}

	std::string Nop::debugExtra() {
		return "<>";
	}

	std::string Nop::toString() const {
		return "<>";
	}
}
