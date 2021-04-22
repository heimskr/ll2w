#include "compiler/Variable.h"
#include "instruction/CopyRInstruction.h"

namespace LL2W {
	CopyRInstruction::CopyRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_,
	int index_):
		RType(rs_, nullptr, rd_, index_), SizedInstruction(size_) {}

	std::string CopyRInstruction::debugExtra() {
		return "\e[2m[\e[22m" + std::string(*rs) + "\e[2m] -> [\e[22m " + std::string(*rd) + "\e[2m]\e[22m" + suffix();
	}

	std::string CopyRInstruction::toString() const {
		return "[" + rs->toString() + "] -> [" + rd->toString() + "]" + suffix();
	}
}
