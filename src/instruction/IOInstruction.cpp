#include "compiler/Variable.h"
#include "instruction/IOInstruction.h"

namespace LL2W {
	IOInstruction::IOInstruction(const std::string *ident_, int index_):
		RType(nullptr, nullptr, nullptr, index_), ident(ident_) {}

	std::string IOInstruction::debugExtra() {
		return ident? "<\e[36mio\e[39m " + *ident + ">" : "<\e[36mio\e[39m>";
	}

	std::string IOInstruction::toString() const {
		return ident? "<io " + *ident + ">" : "<io>";
	}
	
	Instruction * IOInstruction::copy() const {
		return new IOInstruction(*this);
	}
}
