#ifndef COMPILER_LLVMINSTRUCTION_H_
#define COMPILER_LLVMINSTRUCTION_H_

#include "compiler/Instruction.h"

namespace LL2W {
	class InstructionNode;

	class LLVMInstruction: public Instruction {
		public:
			InstructionNode *node;
			bool ownsNode = false;

			LLVMInstruction(InstructionNode *node_, int index_, bool owns_node = false):
				Instruction(index_), node(node_), ownsNode(owns_node) {}

			virtual ~LLVMInstruction();

			bool isTerminal() const override;
			ExtractionResult extract(bool force = false) override;
			std::string debugExtra() override;
			std::string toString() const override;

			bool replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) override;
			bool canReplaceRead(std::shared_ptr<Variable>) const override;
			bool replaceWritten(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) override;
			bool canReplaceWritten(std::shared_ptr<Variable>) const override;

			bool isPhi() const override;
	};
}

#endif
