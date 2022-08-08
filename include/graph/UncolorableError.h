#pragma once

#include <stdexcept>

namespace LL2W {
	struct UncolorableError: public std::runtime_error {
		UncolorableError(): std::runtime_error("Unable to color graph: not enough colors") {}
	};
}
