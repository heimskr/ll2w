#include "compiler/Variable.h"
#include "instruction/SizedStackPopInstruction.h"

namespace LL2W {
	SizedStackPopInstruction::SizedStackPopInstruction(std::shared_ptr<Variable> rd_, int size_, int index_):
		RType(nullptr, nullptr, rd_, index_), size(size_) {}

	SizedStackPopInstruction::SizedStackPopInstruction(std::shared_ptr<Variable> rd_, int index_):
	RType(nullptr, nullptr, rd_, index_) {
		if (rd_->type)
			size = rd_->type->width() / 8;
		else throw std::runtime_error("SizedStackPopInstruction given neither size nor type");
	}

	std::string SizedStackPopInstruction::debugExtra() {
		return "\e[2m]:" + std::to_string(size) + "\e[22m " + std::string(*rd);
	}

	std::string SizedStackPopInstruction::toString() const {
		return "]:" + std::to_string(size) + " " + rd->toString();
	}
}
