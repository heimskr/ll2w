#include "compiler/Variable.h"
#include "instruction/StackStoreInstruction.h"

namespace LL2W {
	ExtractionResult StackStoreInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		// TODO: verify.
		read = {variable};
		// read = {};
		written.clear();
		extracted = true;
		return {read.size(), written.size()};
	}

	std::string StackStoreInstruction::debugExtra() {
		return "\e[1m[store " + std::string(*variable) + "\e[0;1m to " + std::to_string(location.offset) + "]\e[0m";
	}

	bool StackStoreInstruction::operator==(const StackStoreInstruction &other) const {
		return location == other.location && (variable->equivalent(*other.variable) ||
			originalVariable->equivalent(*other.originalVariable));
	}
}
