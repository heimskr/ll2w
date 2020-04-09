#include "compiler/Variable.h"
#include "instruction/LoadSymbolInstruction.h"

namespace LL2W {
	LoadSymbolInstruction::LoadSymbolInstruction(const std::string &imm_, std::shared_ptr<Variable> rd_, int size_,
	int index_):
		IType(nullptr, imm_, rd_, index_), size(size_) {}

	std::string LoadSymbolInstruction::debugExtra() {
		const std::string base = "\e[2m[\e[0;91m&" + imm + "\e[0;2m] ->\e[0m " + std::string(*rd);
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}

	std::string LoadSymbolInstruction::toString() const {
		const std::string base = "[&" + imm + "] -> " + rd->toString();
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}
}
