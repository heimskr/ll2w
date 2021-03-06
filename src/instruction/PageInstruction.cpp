#include "compiler/Variable.h"
#include "instruction/PageInstruction.h"

namespace LL2W {
	PageInstruction::PageInstruction(bool on_, int index_):
		RType(nullptr, nullptr, nullptr, index_), on(on_) {}

	std::string PageInstruction::debugExtra() {
		return "\e[36mpage\e[39m " + std::string(on? "on" : "off");
	}

	std::string PageInstruction::toString() const {
		return "page " + std::string(on? "on" : "off");
	}
}
