#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/SetInstruction.h"
#include "pass/ReplaceObjectsize.h"

namespace LL2W::Passes {
	int replaceObjectsize(Function &function) {
		int replaced_count = 0;
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Call)
				continue;
			
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);
			if (!call->name->isGlobal())
				continue;
			
			GlobalValue *global_name = dynamic_cast<GlobalValue *>(call->name.get());
			if (global_name->name->substr(0, 16) != "llvm.objectsize.")
				continue;

			// Check whether this is a (currently unsupported) dynamic objectsize call.
			if (3 < call->argumentTypes.size()) {
				// If there's a fourth argument, it should be an i1 constant.
				if (IntType *int_type = dynamic_cast<IntType *>(call->argumentTypes.at(3).get())) {
					if (int_type->intWidth != 1)
						throw std::runtime_error("Fourth argument of objectsize intrinsic expected to have width 1");
				} else throw std::runtime_error("Fourth argument of objectsize intrinsic expected to be an integer");
				
				IntValue *int_value = dynamic_cast<IntValue *>(call->constants.at(3)->value.get());
				if (int_value->value != 0)
					throw std::runtime_error("Dynamic objectsize is unsupported");
			}

			LocalValue *local = dynamic_cast<LocalValue *>(call->constants.at(0)->value.get());
			if (!local)
				throw std::runtime_error("First argument of objectsize intrinsic expected to be a local variable");

			IntValue *second = dynamic_cast<IntValue *>(call->constants.at(1)->value.get());
			int out;
			
			// If we don't know the type, the return value depends on the second argument.
			if (!local->variable || !local->variable->type) {
				out = second->value == 0? -1 : 0;
			} else {
				// TODO: is this correct? LLVM's method is more complex.
				out = local->variable->type->width();
			}

			function.insertBefore(instruction, std::make_shared<SetInstruction>(call->variable, out));
			to_remove.push_back(instruction);
			++replaced_count;
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return replaced_count;
	}
}
