#ifndef INSTRUCTION_LOADRINSTRUCTION_H_
#define INSTRUCTION_LOADRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct LoadRInstruction: public RType {
		/** The size of the load in bytes. */
		int size;

		LoadRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rt_, std::shared_ptr<Variable> rd_,
		int size_ = 8, int index_ = -1):
			RType(rs_, rt_, rd_, index_), size(size_) {}

		std::string debugExtra() override;
	};
}

#endif