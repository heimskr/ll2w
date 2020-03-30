#ifndef INSTRUCTION_STORESYMBOLINSTRUCTION_H_
#define INSTRUCTION_STORESYMBOLINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct StoreSymbolInstruction: public IType<std::string> {
		StoreSymbolInstruction(std::shared_ptr<Variable> rs_, std::string imm_, int index_ = -1):
			IType(rs_, imm_, nullptr, index_) {}
		std::string debugExtra() override;
	};
}

#endif
