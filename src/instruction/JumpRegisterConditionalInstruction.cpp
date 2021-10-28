#include "compiler/Variable.h"
#include "instruction/JumpRegisterConditionalInstruction.h"

namespace LL2W {
	ExtractionResult JumpRegisterConditionalInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();

		if (rs)
			read.insert(rs);
		if (rd) // I'm foolish and put a variable that's read—not written to—in rd. It really should be rt.
			read.insert(rd);

		extracted = true;
		return {read.size(), written.size()};
	}

	std::string JumpRegisterConditionalInstruction::debugExtra() {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m " + std::string(*rd) + " \e[2mif\e[22m " +
			std::string(*rs);
	}

	std::string JumpRegisterConditionalInstruction::toString() const {
		return std::string(link? "::" : ":") + " " + rd->toString() + " if " + rs->toString();
	}
}
