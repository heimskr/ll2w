#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/IgnoreIntrinsics.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	int ignoreIntrinsics(Function &function) {
		Timer timer("IgnoreInstrinsics");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->getNodeType() != NodeType::Call) {
				continue;
			}

			CallNode *call = dynamic_cast<CallNode *>(llvm->getNode());
			if (!call->name->isGlobal()) {
				continue;
			}

			GlobalValue *global_name = dynamic_cast<GlobalValue *>(call->name.get());

			std::string_view name(*global_name->name);

			if (name.starts_with("@llvm.lifetime.") || name.starts_with("@llvm.dbg.")) {
				to_remove.push_back(instruction);
			} else if (name == "@llvm.experimental.noalias.scope.decl") {
				to_remove.push_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return to_remove.size();
	}
}