#include "compiler/Variable.h"
#include "instruction/StackLoadInstruction.h"

namespace LL2W {
	ExtractionResult StackLoadInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written = {result};
		extracted = true;
		return {read.size(), written.size()};
	}

	std::string StackLoadInstruction::debugExtra() {
		return "\e[1m[load " + std::string(*result) + " @ " + std::to_string(location.offset) + "]\e[0m";
	}
}