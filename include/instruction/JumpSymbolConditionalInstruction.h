#ifndef INSTRUCTIONS_JUMPSYMBOLCONDITIONALINSTRUCTION_H_
#define INSTRUCTIONS_JUMPSYMBOLCONDITIONALINSTRUCTION_H_

#include <sstream>

#include "instruction/JType.h"

namespace LL2W {
	/**
	 * : &symbol if $rs
	 */
	struct JumpSymbolConditionalInstruction: public JType<std::string> {
		using JType::JType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
