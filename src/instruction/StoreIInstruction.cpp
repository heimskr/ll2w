#include "compiler/Variable.h"
#include "instruction/StoreIInstruction.h"

namespace LL2W {
	StoreIInstruction::StoreIInstruction(std::shared_ptr<Variable> rs_, ValueType imm_, int size_, int index_):
		IType(rs_, imm_, nullptr, index_), SizedInstruction(size_) {}

	std::string StoreIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-> [\e[22;91m" + std::to_string(imm) + "\e[39;2m]\e[22m" + suffix();
	}

	std::string StoreIInstruction::toString() const {
		return rs->toString() + " -> [" + std::to_string(imm) + "]" + suffix();
	}
}
