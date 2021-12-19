#include "compiler/Variable.h"
#include "instruction/SvringInstruction.h"

namespace LL2W {
	SvringInstruction::SvringInstruction(std::shared_ptr<Variable> rs_, int index_):
		RType(rs_, nullptr, nullptr, index_) {}

	std::string SvringInstruction::debugExtra() {
		return "\e[36m%ring\e[39m \e[2m->\e[22m " + std::string(*rs);
	}

	std::string SvringInstruction::toString() const {
		return "%ring -> " + rs->toString();
	}
}
