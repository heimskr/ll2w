#include "compiler/Variable.h"
#include "instruction/PageStackInstruction.h"

namespace LL2W {
	PageStackInstruction::PageStackInstruction(bool is_push, VariablePtr rs_):
		RType(rs_, nullptr, nullptr, index_), isPush(is_push) {}

	std::string PageStackInstruction::debugExtra() const {
		if (!rs)
			return "\e[2m" + std::string(isPush? "[" : "]") + "\e[22m \e[34m%page\e[39m";
		return "\e[2m: " + std::string(isPush? "[" : "]") + "\e[22m \e[34m%page\e[39m " + std::string(*rs);
	}

	std::string PageStackInstruction::toString() const {
		if (!rs)
			return std::string(isPush? "[" : "]") + " %page";
		return ": " + std::string(isPush? "[" : "]") + " %page " + rs->toString();
	}

	Instruction * PageStackInstruction::copy() const {
		return new PageStackInstruction(*this);
	}
}
