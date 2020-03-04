#ifndef INSTRUCTION_SET_H_
#define INSTRUCTION_SET_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	class SetInstruction: public WhyInstruction {
		public:
			std::shared_ptr<Variable> rd;
			int imm;

			SetInstruction(std::shared_ptr<Variable> rd_, int imm_, int index_):
				WhyInstruction(index_), rd(rd_), imm(imm_) {}
			
			std::string debugExtra() override;
	};
}

#endif
