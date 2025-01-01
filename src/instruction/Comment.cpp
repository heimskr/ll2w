#include "compiler/Variable.h"
#include "instruction/Comment.h"

namespace LL2W {
	Comment::Comment(std::string text):
		text(std::move(text)) {}

	std::string Comment::debugExtra() const {
		return "\e[35m// " + text + "\e[22;39m";
	}

	std::string Comment::toString() const {
		return "// " + text;
	}

	Instruction * Comment::copy() const {
		return new Comment(*this);
	}
}
