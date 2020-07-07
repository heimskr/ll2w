#ifndef UNCOLORABLEERROR_H_
#define UNCOLORABLEERROR_H_

#include <stdexcept>

namespace LL2W {
	struct UncolorableError: public std::runtime_error {
		UncolorableError(): std::runtime_error("Unable to color graph: not enough colors") {}
	};
}

#endif
