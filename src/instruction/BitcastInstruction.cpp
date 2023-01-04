#include "compiler/Function.h"
#include "compiler/Variable.h"
#include "instruction/BitcastInstruction.h"

namespace LL2W {
	BitcastInstruction::BitcastInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		LinkedSD(std::move(rs_), nullptr, std::move(rd_), index_) {}

	BitcastInstruction::BitcastInstruction(VariablePtr rs_, Function &function, TypePtr new_type, BasicBlockPtr block,
	                                       int index_):
	LinkedSD(std::move(rs_), nullptr, nullptr, index_) {
		rd = function.newVariable(std::move(new_type), block);
		rd->typeOverride = true;
		rd->makeAliasOf(rs);
	}

	std::string BitcastInstruction::debugExtra() const {
		return "bc " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string BitcastInstruction::toString() const {
		return "bc " + rs->toString() + " -> " + rd->toString();
	}
	
	Instruction * BitcastInstruction::copy() const {
		return new BitcastInstruction(*this);
	}
}
