#include "compiler/Variable.h"
#include "instruction/Nop.h"

namespace LL2W {
	Nop::Nop() = default;

	std::string Nop::debugExtra() const {
		return "<>";
	}

	std::string Nop::toString() const {
		return "<>";
	}

	Instruction * Nop::copy() const {
		return new Nop(*this);
	}
}
