#include "compiler/Variable.h"
#include "instruction/PageStackInstruction.h"

namespace LL2W {
	PageStackInstruction::PageStackInstruction(bool is_push, int index_):
		RType(nullptr, nullptr, nullptr, index_), isPush(is_push) {}

	std::string PageStackInstruction::debugExtra() {
		return "\e[2m" + std::string(isPush? "[" : "]") + "\e[22m \e[34m%page\e[39m";
	}

	std::string PageStackInstruction::toString() const {
		return std::string(isPush? "[" : "]") + " %page";
	}
}
