#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/SetInstruction.h"
#include "pass/IgnoreIntrinsics.h"

namespace LL2W::Passes {
	int ignoreIntrinsics(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Call)
				continue;
			
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);
			if (!call->name->isGlobal())
				continue;
			
			GlobalValue *global_name = dynamic_cast<GlobalValue *>(call->name.get());
			if (global_name->name->substr(0, 14) == "llvm.lifetime.")
				to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}