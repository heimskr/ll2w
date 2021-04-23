#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/WhyInfo.h"
#include "pass/LowerInlineAsm.h"
#include "util/Util.h"

namespace LL2W::Passes {
	int lowerInlineAsm(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (auto iter = function.linearInstructions.begin(); iter != function.linearInstructions.end(); ++iter) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(iter->get());
			if (!llvm || llvm->node->nodeType() != NodeType::Asm)
				continue;

			AsmNode *asm_node = dynamic_cast<AsmNode *>(llvm->node);
			info() << "Asm: " << asm_node->debugExtra() << "\n";

			auto copy = iter;
			for (++copy; copy != function.linearInstructions.end(); ++copy) {
				LLVMInstruction *inner_llvm = dynamic_cast<LLVMInstruction *>(copy->get());
				if (!inner_llvm || inner_llvm->node->nodeType() != NodeType::ExtractValue)
					break;
				
				ExtractValueNode *extract = dynamic_cast<ExtractValueNode *>(inner_llvm->node);
				if (*extract->aggregateType != *asm_node->returnType)
					break;

				info() << "EV: " << extract->debugExtra() << "\n";
			}
		}

		return 0;
	}
}
