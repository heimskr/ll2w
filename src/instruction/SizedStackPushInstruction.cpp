#include "compiler/Variable.h"
#include "instruction/SizedStackPushInstruction.h"

namespace LL2W {
	SizedStackPushInstruction::SizedStackPushInstruction(std::shared_ptr<Variable> rs_, int size_, int index_):
		RType(rs_, nullptr, nullptr, index_), size(size_) {}

	SizedStackPushInstruction::SizedStackPushInstruction(std::shared_ptr<Variable> rs_, int index_):
	RType(rs_, nullptr, nullptr, index_) {
		if (rs_->type)
			size = rs_->type->width() / 8;
		else throw std::runtime_error("SizedStackPushInstruction given neither size nor type");
	}

	std::string SizedStackPushInstruction::debugExtra() {
		return "\e[2m[:" + std::to_string(size) + "\e[22m " + std::string(*rs);
	}

	std::string SizedStackPushInstruction::toString() const {
		return "[:" + std::to_string(size) + " " + rs->toString();
	}
}
