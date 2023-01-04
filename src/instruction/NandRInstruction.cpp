#include "compiler/Variable.h"
#include "instruction/NandRInstruction.h"

namespace LL2W {
	std::string NandRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m~&\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string NandRInstruction::toString() const {
		return rs->toString() + " ~& " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * NandRInstruction::copy() const {
		return new NandRInstruction(*this);
	}
}
