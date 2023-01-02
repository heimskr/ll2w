#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Transforms the label of any J-type instruction with needsTransformation == true. */
	size_t transformLabels(Function &);
}
