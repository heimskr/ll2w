#ifndef INSTRUCTIONS_JUMPSYMBOLINSTRUCTION_H_
#define INSTRUCTIONS_JUMPSYMBOLINSTRUCTION_H_

#include "instruction/JType.h"

namespace LL2W {
	struct JumpSymbolInstruction: public JType<int> {
		std::string symbol;

		JumpSymbolInstruction(std::shared_ptr<Variable> rs_, const std::string &symbol_, bool link_, int index_ = -1):
			JType(rs_, -1, link_, index_), symbol(symbol_) {}

		std::string debugExtra() override;
	};
}

#endif
