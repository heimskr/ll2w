#include "compiler/Variable.h"
#include "instruction/Comment.h"

namespace LL2W {
	Comment::Comment(const std::string &text_, int index_): WhyInstruction(index_), text(text_) {}

	std::string Comment::debugExtra() {
		return "\e[35m// " + text + "\e[22;39m";
	}

	std::string Comment::toString() const {
		return "// " + text;
	}
}
