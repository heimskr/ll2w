#include "instruction/HasSize.h"

#include <csignal>

namespace LL2W {
	HasSize::HasSize(WASMSize size):
		size(size) {
			// if (int(size) == 3) raise(SIGTRAP);
		}

	std::string HasSize::sizeSuffix() const {
		switch (size) {
			case WASMSize::Word:  return "";
			case WASMSize::Half:  return " /h";
			case WASMSize::Short: return " /s";
			case WASMSize::Byte:  return " /b";
			default:
				return std::format(" /{}?", static_cast<int>(size));
		}
	}
}
