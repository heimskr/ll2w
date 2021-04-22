#include "compiler/Variable.h"
#include "instruction/NandIInstruction.h"

namespace LL2W {
	std::string NandIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m~&\e[0m " + colorize(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string NandIInstruction::toString() const {
		return rs->toString() + " ~& " + LL2W::toString(imm) + " -> " + rd->toString();
	}
}
