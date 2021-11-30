#include "compiler/Variable.h"
#include "instruction/JumpRegisterInstruction.h"

namespace LL2W {
	ExtractionResult JumpRegisterInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		if (rd && !secretReads)
			read.insert(rd); // I'm foolish and put a variable that's read—not written to—in rd. It really should be rs.

		return {read.size(), written.size()};
	}

	std::string JumpRegisterInstruction::debugExtra() {
		return "\e[2m" + conditionPrefix() + std::string(link? "::" : ":") + "\e[0m " + std::string(*rd);
	}

	std::string JumpRegisterInstruction::toString() const {
		return conditionPrefix() + std::string(link? "::" : ":") + " " + rd->toString();
	}

	bool JumpRegisterInstruction::alwaysTerminal() const {
		return condition == Condition::None;
	}
}
