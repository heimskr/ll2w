#pragma once

#include <string>

namespace LL2W {
	struct SizedInstruction {
		/** The size of the instruction in bytes. */
		int size;
		SizedInstruction(int size_);
		std::string suffix() const;
	};
}
