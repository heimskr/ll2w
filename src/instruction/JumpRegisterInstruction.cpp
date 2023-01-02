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

	bool JumpRegisterInstruction::replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) {
		if (rd && rd->isAliasOf(*to_replace)) {
			rd = new_var;
			return true;
		}

		return false;
	}

	bool JumpRegisterInstruction::canReplaceRead(const VariablePtr &to_replace) const {
		return rd && rd->isAliasOf(*to_replace);
	}

	bool JumpRegisterInstruction::replaceWritten(const VariablePtr &, const VariablePtr &) {
		return false;
	}

	bool JumpRegisterInstruction::canReplaceWritten(const VariablePtr &) const {
		return false;
	}

	std::string JumpRegisterInstruction::debugExtra() {
		return "\e[2m" + conditionPrefix() + std::string(link? "::" : ":") + "\e[0m " + std::string(*rd);
	}

	std::string JumpRegisterInstruction::toString() const {
		return conditionPrefix() + std::string(link? "::" : ":") + " " + rd->toString();
	}

	bool JumpRegisterInstruction::isBlockTerminal() const {
		return condition == Condition::None;
	}
}
