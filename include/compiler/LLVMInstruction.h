#pragma once

#include "compiler/Instruction.h"

namespace LL2W {
	class InstructionNode;

	class LLVMInstruction: public Instruction {
		public:
			InstructionNode *node;
			bool ownsNode = false;

			LLVMInstruction(InstructionNode *node_, int index_, bool owns_node = false);

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
			bool holdsLabels() const override;
			bool replaceLabel(const std::string *, const std::string *) override;
			std::vector<const std::string *> getLabels() const override;
	};
}
