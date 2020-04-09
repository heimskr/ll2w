#include "compiler/Variable.h"
#include "instruction/StoreSymbolInstruction.h"

namespace LL2W {
	std::string StoreSymbolInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-> [\e[22;91m&" + imm + "\e[39;2m]\e[22m" + suffix();
	}

	std::string StoreSymbolInstruction::toString() const {
		return rs->toString() + " -> [&" + imm + "]" + suffix();
	}
}
