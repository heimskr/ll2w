#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/SetInstruction.h"
#include "pass/LowerObjectsize.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	int lowerObjectsize(Function &function) {
		Timer timer("LowerObjectsize");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->getNodeType() != NodeType::Call)
				continue;

			CallNode *call = dynamic_cast<CallNode *>(llvm->getNode());
			if (!call->name->isGlobal())
				continue;

			GlobalValue *global_name = dynamic_cast<GlobalValue *>(call->name.get());
			if (global_name->name->substr(0, 16) != "llvm.objectsize.")
				continue;

			// Check whether this is a (currently unsupported) dynamic objectsize call.
			if (3 < call->argumentTypes.size()) {
				// If there's a fourth argument, it should be an i1 constant.
				if (IntType *int_type = dynamic_cast<IntType *>(call->argumentTypes.at(3).get())) {
					if (int_type->bitWidth != 1)
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

			function.insertBefore(instruction, std::make_shared<SetInstruction>(call->variable, out))
				->setDebug(llvm)->extract();
			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
