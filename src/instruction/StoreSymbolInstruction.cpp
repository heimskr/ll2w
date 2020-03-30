#include "compiler/Variable.h"
#include "instruction/StoreSymbolInstruction.h"

namespace LL2W {
	std::string StoreSymbolInstruction::debugExtra() {
		const std::string base = std::string(*rs) + " \e[2m-> [\e[22;91m&" + imm + " \e[39;2m]\e[22m";
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}
}
