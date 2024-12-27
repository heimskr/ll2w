#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "instruction/JType.h"
#include "pass/TransformLabels.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t transformLabels(Function &function) {
		Timer timer{"TransformLabels"};
		size_t changed = 0;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			if (auto jtype = std::dynamic_pointer_cast<JType<>>(instruction)) {
				if (jtype->needsTransformation) {
					const auto transformed = function.transformLabel(*std::get<const std::string *>(jtype->addr));
					jtype->addr = StringSet::intern(transformed);
					jtype->needsTransformation = false;
					++changed;
				}
			}
		}

		return changed;
	}
}
