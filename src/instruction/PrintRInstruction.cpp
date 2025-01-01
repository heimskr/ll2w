#include "compiler/Variable.h"
#include "instruction/PrintRInstruction.h"

namespace LL2W {
	PrintRInstruction::PrintRInstruction(std::shared_ptr<Variable> rs_, PrintType type_):
		RType(std::move(rs_), nullptr, nullptr), type(type_) {}

	std::string PrintRInstruction::debugExtra() const {

		return "<\e[36m" + std::string(typeName()) + "\e[39m " + std::string(*rs) + ">";
	}

	std::string PrintRInstruction::toString() const {
		return "<" + std::string(typeName()) + " " + rs->toString() + ">";
	}

	const char * PrintRInstruction::typeName() const {
		switch (type) {
			case PrintType::Bin:  return "prb";
			case PrintType::Dec:  return "prd";
			case PrintType::Hex:  return "prx";
			case PrintType::Char: return "prc";
			case PrintType::Full: return "print";
			default: return "???";
		}
	}

	Instruction * PrintRInstruction::copy() const {
		return new PrintRInstruction(*this);
	}
}
