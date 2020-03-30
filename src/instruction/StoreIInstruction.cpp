#include "compiler/Variable.h"
#include "instruction/StoreIInstruction.h"

namespace LL2W {
	StoreIInstruction::StoreIInstruction(std::shared_ptr<Variable> rs_, int imm_, int size_, int index_):
		IType(rs_, imm_, nullptr, index_), size(size_) {}

	std::string StoreIInstruction::debugExtra() {
		const std::string base = std::string(*rs) + " \e[2m-> [\e[22;91m" + std::to_string(imm) + "\e[39;2m]\e[22m";
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}
}
