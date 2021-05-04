#include "compiler/Variable.h"
#include "instruction/QueryInstruction.h"

namespace LL2W {
	std::string QueryInstruction::debugExtra() {
		return "? \e[36m" + query_map.at(type) + "\e[39m \e[2m->\e[22m " + std::string(*rd);
	}

	std::string QueryInstruction::toString() const {
		return "? " + query_map.at(type) + " -> " + rd->toString();
	}
}
