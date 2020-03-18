#include "compiler/Variable.h"
#include "instruction/StackPushInstruction.h"

namespace LL2W {
	StackPushInstruction::StackPushInstruction(std::shared_ptr<Variable> rs_, int index_):
		RType(rs_, nullptr, nullptr, index_) {}

	std::string StackPushInstruction::debugExtra() {
		return "\e[2m[\e[22m " + std::string(*rs);
	}
}
