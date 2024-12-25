#pragma once

#include "parser/Enums.h"

namespace LL2W {
	struct HasSize {
		WASMSize size = WASMSize::Word;

		HasSize(WASMSize size):
			size(size) {}

		inline std::string sizeSuffix() const {
			switch (size) {
				case WASMSize::Word:  return "";
				case WASMSize::Half:  return " /h";
				case WASMSize::Short: return " /s";
				case WASMSize::Byte:  return " /b";
				default:
					return " /?";
			}
		}
	};
}
