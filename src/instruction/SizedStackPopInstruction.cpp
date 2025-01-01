#include "compiler/Variable.h"
#include "instruction/SizedStackPopInstruction.h"

namespace LL2W {
	SizedStackPopInstruction::SizedStackPopInstruction(VariablePtr rd, int size):
		RType(nullptr, nullptr, std::move(rd)), size(size) {}

	SizedStackPopInstruction::SizedStackPopInstruction(VariablePtr rd_):
	RType(nullptr, nullptr, std::move(rd_)) {
		if (rd->type) {
			size = rd->type->width() / 8;
		}
		else throw std::runtime_error("SizedStackPopInstruction given neither size nor type");
	}

	std::string SizedStackPopInstruction::debugExtra() const {
		return "\e[2m]:" + std::to_string(size) + "\e[22m " + std::string(*rd);
	}

	std::string SizedStackPopInstruction::toString() const {
		return "]:" + std::to_string(size) + " " + rd->toString();
	}

	Instruction * SizedStackPopInstruction::copy() const {
		return new SizedStackPopInstruction(*this);
	}
}
