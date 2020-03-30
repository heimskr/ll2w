#ifndef INSTRUCTION_STORESYMBOLINSTRUCTION_H_
#define INSTRUCTION_STORESYMBOLINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * $rs -> [&symbol]
	 */
	struct StoreSymbolInstruction: public IType<std::string> {
		/** The size of the store in bytes. */
		int size;

		StoreSymbolInstruction(std::shared_ptr<Variable> rs_, const std::string &imm_, int size_, int index_ = -1):
			IType(rs_, imm_, nullptr, index_), size(size_) {}

		std::string debugExtra() override;
	};
}

#endif
