#include "compiler/Variable.h"
#include "instruction/LoadRInstruction.h"

namespace LL2W {
	std::string LoadRInstruction::debugExtra() {
		const std::string base = "\e[2m[\e[0;91m" + std::string(*rs) + "\e[0;2m] ->\e[0m " + std::string(*rd);
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}
}
