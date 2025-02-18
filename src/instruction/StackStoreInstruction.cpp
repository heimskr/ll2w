#include "compiler/Variable.h"
#include "instruction/StackStoreInstruction.h"

namespace LL2W {
	ExtractionResult StackStoreInstruction::extract(bool force) {
		if (extracted && !force) {
			return {read.size(), written.size()};
		}

		read.clear();
		written.clear();
		extracted = true;

		if (!secretReads) {
			// TODO: verify.
			read = {variable};
			// read = {};
		}

		return {read.size(), written.size()};
	}

	std::string StackStoreInstruction::debugExtra() const {
		return "\e[1m[store " + std::string(*variable) + "\e[1m to " + std::to_string(location.offset) + "]\e[22m";
	}

	bool StackStoreInstruction::operator==(const Instruction &other_instruction) const {
		if (const auto *other = dynamic_cast<const StackStoreInstruction *>(&other_instruction)) {
			return location == other->location && (variable->equivalent(*other->variable) || originalVariable->equivalent(*other->originalVariable));
		}
		return false;
	}

	Instruction * StackStoreInstruction::copy() const {
		return new StackStoreInstruction(*this);
	}
}
