#include "compiler/Variable.h"
#include "instruction/StackLoadInstruction.h"

namespace LL2W {
	ExtractionResult StackLoadInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		if (!secretWrites)
			// TODO: verify.
			written = {result};

		return {read.size(), written.size()};
	}

	std::string StackLoadInstruction::debugExtra() {
		return "\e[1m[load  " + std::string(*result) + "\e[1m from " + std::to_string(location.offset) + "]\e[22m";
	}
}
