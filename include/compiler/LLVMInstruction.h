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
			std::string debugExtra() const override;
			std::string toString() const override;

			bool replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) override;
			bool canReplaceRead(const VariablePtr &) const override;
			bool replaceWritten(const VariablePtr &to_replace, const VariablePtr &new_var) override;
			bool canReplaceWritten(const VariablePtr &) const override;

			bool isPhi() const override;
			bool holdsLabels() const override;
			bool replaceLabel(const std::string *, const std::string *) override;
			std::vector<const std::string *> getLabels() const override;

			bool isBlockTerminal() const override;

			Instruction * copy() const override;
	};
}
