#pragma once

namespace LL2W {
	enum class InstructionMeta {
		LoadArgumentsSkip,
		// Any instruction with this tag won't be considered when determining whether a clobber is live.
		IgnoreForClobbers,
	};
}
