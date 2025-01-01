#include "compiler/Variable.h"
#include "instruction/QueryInstruction.h"

namespace LL2W {
	QueryInstruction::QueryInstruction(QueryType type_, VariablePtr rd_):
		RType(nullptr, nullptr, std::move(rd_)), type(type_) {}

	std::string QueryInstruction::debugExtra() const {
		return "? \e[36m" + query_map.at(type) + "\e[39m \e[2m->\e[22m " + std::string(*rd);
	}

	std::string QueryInstruction::toString() const {
		return "? " + query_map.at(type) + " -> " + rd->toString();
	}

	Instruction * QueryInstruction::copy() const {
		return new QueryInstruction(*this);
	}
}
