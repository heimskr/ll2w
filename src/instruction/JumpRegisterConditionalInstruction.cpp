#include "compiler/Variable.h"
#include "instruction/JumpRegisterConditionalInstruction.h"

namespace LL2W {
	ExtractionResult JumpRegisterConditionalInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		if (rs && !secretReads)
			read.insert(rs);
		if (rd && !secretReads) // I'm foolish and put a variable that's read—not written to—in rd. It really should be rt.
			read.insert(rd);

		return {read.size(), written.size()};
	}

	bool JumpRegisterConditionalInstruction::replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) {
		bool changed = false;

		if (rs && rs->isAliasOf(*to_replace)) {
			rs = new_var;
			changed = true;
		}

		if (rd && rd->isAliasOf(*to_replace)) {
			rd = new_var;
			changed = true;
		}

		return changed;
	}

	bool JumpRegisterConditionalInstruction::canReplaceRead(const VariablePtr &to_replace) const {
		return (rs && rs->isAliasOf(*to_replace)) || (rd && rd->isAliasOf(*to_replace));
	}

	bool JumpRegisterConditionalInstruction::replaceWritten(const VariablePtr &, const VariablePtr &) {
		return false;
	}

	bool JumpRegisterConditionalInstruction::canReplaceWritten(const VariablePtr &) const {
		return false;
	}

	std::string JumpRegisterConditionalInstruction::debugExtra() const {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m " + std::string(*rd) + " \e[2mif\e[22m " +
			std::string(*rs);
	}

	std::string JumpRegisterConditionalInstruction::toString() const {
		return std::string(link? "::" : ":") + " " + rd->toString() + " if " + rs->toString();
	}
	
	Instruction * JumpRegisterConditionalInstruction::copy() const {
		return new JumpRegisterConditionalInstruction(*this);
	}
}
