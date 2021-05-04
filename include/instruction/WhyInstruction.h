#ifndef COMPILER_WHYINSTRUCTION_H_
#define COMPILER_WHYINSTRUCTION_H_

#include "compiler/Instruction.h"

namespace LL2W {
	class WhyInstruction: public Instruction {
		protected:
			using Instruction::Instruction;

		public:
			bool isTerminal() const override { return false; }
			std::pair<char, char> extract(bool = false) override { return {0, 0}; }
			virtual bool alwaysTerminal() const { return false; }
	};
}

#endif
