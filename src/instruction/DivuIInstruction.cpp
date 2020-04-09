#include "compiler/Variable.h"
#include "instruction/DivuIInstruction.h"

namespace LL2W {
	std::string DivuIInstruction::debugExtra() {
		return operDebug("/") + " /u";
	}

	std::string DivuIInstruction::toString() const {
		return operString("/") + " /u";
	}
}
