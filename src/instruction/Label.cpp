#include "compiler/Variable.h"
#include "instruction/Label.h"

namespace LL2W {
	Label::Label(std::string name):
		name(std::move(name)) {}

	std::string Label::debugExtra() const {
		return "\e[94m@" + name + "\e[39m";
	}

	std::string Label::toString() const {
		return "@" + name;
	}

	Instruction * Label::copy() const {
		return new Label(*this);
	}
}
