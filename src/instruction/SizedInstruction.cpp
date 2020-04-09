#include "instruction/SizedInstruction.h"

namespace LL2W {
	SizedInstruction::SizedInstruction(int size_): size(size_) {}
	
	std::string SizedInstruction::suffix() const {
		switch (size) {
			case 8:  return "";
			case 4:  return " /h";
			case 2:  return " /s";
			case 1:  return " /b";
			default: return " /" + std::to_string(size);
		}
	}
}