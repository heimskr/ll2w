#include "compiler/Variable.h"
#include "instruction/LogicalNotRInstruction.h"

namespace LL2W {
	std::string LogicalNotRInstruction::debugExtra() {
		if (rs == rd)
			return "\e[2m!\e[22m" + std::string(*rs) + "\e[2m.\e[22m";
		return "\e[2m!\e[22m" + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}
}
