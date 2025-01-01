#include "compiler/Variable.h"
#include "instruction/PageInstruction.h"

namespace LL2W {
	PageInstruction::PageInstruction(bool on_):
		RType(nullptr, nullptr, nullptr), on(on_) {}

	std::string PageInstruction::debugExtra() const {
		return "\e[36m%page\e[39m " + std::string(on? "on" : "off");
	}

	std::string PageInstruction::toString() const {
		return "%page " + std::string(on? "on" : "off");
	}

	Instruction * PageInstruction::copy() const {
		return new PageInstruction(*this);
	}
}
