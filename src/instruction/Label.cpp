#include "compiler/Variable.h"
#include "instruction/Label.h"

namespace LL2W {
	Label::Label(const std::string &name_, int index_): WhyInstruction(index_), name(name_) {}

	std::string Label::debugExtra() {
		return "\e[94m@" + name + "\e[39m";
	}

	std::string Label::toString() const {
		return "@" + name;
	}
}
