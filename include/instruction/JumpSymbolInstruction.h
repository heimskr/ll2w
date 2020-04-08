#ifndef INSTRUCTIONS_JUMPSYMBOLINSTRUCTION_H_
#define INSTRUCTIONS_JUMPSYMBOLINSTRUCTION_H_

#include "instruction/JType.h"

namespace LL2W {
	struct JumpSymbolInstruction: public JType<int> {
		std::string symbol;

		JumpSymbolInstruction(const std::string &symbol_, bool link_, int index_ = -1):
			JType(nullptr, -1, link_, index_), symbol(symbol_) {}

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
