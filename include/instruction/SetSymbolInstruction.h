#ifndef INSTRUCTION_SETSYMBOLINSTRUCTION_H_
#define INSTRUCTION_SETSYMBOLINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * &symbol -> $rd
	 */
	struct SetSymbolInstruction: public IType<std::string> {
		SetSymbolInstruction(std::shared_ptr<Variable> rd_, std::string imm_, int index_ = -1):
			IType(nullptr, imm_, rd_, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
