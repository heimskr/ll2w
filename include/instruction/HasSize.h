#pragma once

#include "parser/Enums.h"

#include <format>

namespace LL2W {
	struct HasSize {
		WASMSize size = WASMSize::Word;

		HasSize(WASMSize);

		std::string sizeSuffix() const;
	};
}
