#ifndef INSTRUCTION_LOADSYMBOLINSTRUCTION_H_
#define INSTRUCTION_LOADSYMBOLINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * [&symbol] -> $rd
	 */
	struct LoadSymbolInstruction: public IType<std::string> {
		/** The size of the load in bytes. */
		int size;

		LoadSymbolInstruction(const std::string &imm_, std::shared_ptr<Variable> rd_, int size_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
