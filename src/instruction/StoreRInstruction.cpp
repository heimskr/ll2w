#include "compiler/Variable.h"
#include "instruction/StoreRInstruction.h"

namespace LL2W {
	StoreRInstruction::StoreRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_,
	int index_):
		RType(rs_, nullptr, rd_, index_), size(size_) {}

	std::string StoreRInstruction::debugExtra() {
		const std::string base = std::string(*rs) + " \e[2m-> [\e[22;91m" + std::string(*rd) + "\e[39;2m]\e[22m";
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}
}
