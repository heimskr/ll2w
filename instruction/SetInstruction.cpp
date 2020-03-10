#include "compiler/Variable.h"
#include "instruction/SetInstruction.h"

namespace LL2W {
	ExtractionResult SetInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written = {rd};
		extracted = true;
		return {read.size(), written.size()};
	}

	std::string SetInstruction::debugExtra() {
		return "\e[91m" + std::to_string(imm) + " \e[0;2m->\e[0;32m " + std::string(*rd) + "\e[0m";
	}
}