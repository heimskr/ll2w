#include "compiler/Variable.h"
#include "instruction/StoreRInstruction.h"

namespace LL2W {
	StoreRInstruction::StoreRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_,
	int index_):
		RType(rs_, nullptr, rd_, index_), SizedInstruction(size_) {}

	std::string StoreRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-> [\e[22;91m" + std::string(*rd) + "\e[39;2m]\e[22m" + suffix();
	}

	std::string StoreRInstruction::toString() const {
		return rs->toString() + " -> [" + rd->toString() + "]" + suffix();
	}
}
