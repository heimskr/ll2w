#include "compiler/Variable.h"
#include "instruction/LoadIInstruction.h"

namespace LL2W {
	LoadIInstruction::LoadIInstruction(int imm_, std::shared_ptr<Variable> rd_, int size_, int index_):
		IType(nullptr, imm_, rd_, index_), size(size_) {}

	std::string LoadIInstruction::debugExtra() {
		const std::string base = "\e[2m[\e[0;91m" + std::to_string(imm) + "\e[0;2m] ->\e[0m " + std::string(*rd);
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}

	std::string LoadIInstruction::toString() const {
		const std::string base = "[" + std::to_string(imm) + "] -> " + rd->toString();
		switch (size) {
			case 8:  return base;
			case 4:  return base + " /h";
			case 2:  return base + " /s";
			case 1:  return base + " /b";
			default: return base + " /" + std::to_string(size);
		}
	}
}
