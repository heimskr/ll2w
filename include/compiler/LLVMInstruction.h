#ifndef COMPILER_LLVMINSTRUCTION_H_
#define COMPILER_LLVMINSTRUCTION_H_

#include "compiler/Instruction.h"

namespace LL2W {
	struct InstructionNode;

	class LLVMInstruction: public Instruction {
		public:
			InstructionNode *node;

			LLVMInstruction(InstructionNode *node_, int index_): Instruction(index_), node(node_) {}

			bool isTerminal() const override;
			ExtractionResult extract(bool force = false) override;
			std::string debugExtra() override;
	};
}

#endif
