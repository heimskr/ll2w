#include "compiler/Function.h"
#include "compiler/Variable.h"
#include "instruction/BitcastInstruction.h"

namespace LL2W {
	BitcastInstruction::BitcastInstruction(VariablePtr rs, VariablePtr rd):
		LinkedSD(std::move(rs), nullptr, std::move(rd)) {}

	BitcastInstruction::BitcastInstruction(VariablePtr rs_, Function &function, TypePtr new_type, BasicBlockPtr block):
		LinkedSD(std::move(rs_), nullptr, nullptr) {
			if (function.variableFreeze) {
				if (rs->registers.size() != 1) {
					info() << "rs registers: " << rs->registersString() << " in " << *rs << "\n";
					info() << "rs defs (" << rs->definitions.size() << "):\n";
					for (const auto &weak: rs->definitions) {
						if (auto strong = weak.lock()) {
							info() << " - " << *strong << "\n";
						}
					}
				}
				assert(rs->registers.size() == 1);
				rd = function.makePrecoloredVariable(static_cast<uint8_t>(*rs->registers.begin()), block);
				rd->type = std::move(new_type);
			} else {
				rd = function.newVariable(std::move(new_type), block);
			}

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
