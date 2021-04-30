#ifndef INSTRUCTION_SIZEDINSTRUCTION_H_
#define INSTRUCTION_SIZEDINSTRUCTION_H_

#include <string>

namespace LL2W {
	struct SizedInstruction {
		/** The size of the load in bytes. */
		int size;
		SizedInstruction(int size_);
		std::string suffix() const;
	};
}

#endif
