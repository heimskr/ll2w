#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "compiler/Variable.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/JumpInstruction.h"
#include "instruction/LoadIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StackPopInstruction.h"
#include "instruction/StackPushInstruction.h"
#include "pass/LowerMemcpy.h"
#include "pass/LowerMemset.h"
#include "util/Util.h"

namespace LL2W::Passes {
	size_t lowerMemcpy(Function &function) {
		size_t replaced = 0;
		std::list<InstructionPtr> to_remove, &linear = function.linearInstructions;

		for (auto iter = linear.begin(), end = linear.end(); iter != end;) {
			InstructionPtr &instruction = *iter;
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Call) {
				++iter;
				continue;
			}
			CallNode *call = dynamic_cast<CallNode *>(llvm->node);
			if (!call->name->isGlobal()) {
				++iter;
				continue;
			}
			BasicBlockPtr block = instruction->parent.lock();
			GlobalValue *global = dynamic_cast<GlobalValue *>(call->name.get());
			const std::string &name = *global->name;
			if (name.substr(0, sizeof("llvm.memcpy.") - 1) != "llvm.memcpy.") {
				++iter;
				continue;
			}

			if (name == "llvm.memcpy.p0i8.p0i8.i64") {
				try {
					VariablePtr dest_arg, src_arg, len_arg;

					ConstantPtr converted0 = call->constants[0]->convert(),
					            converted1 = call->constants[1]->convert(),
					            converted2 = call->constants[2]->convert();

					setupMemsetValue(function, converted0, instruction, dest_arg, false);
					setupMemsetValue(function, converted1, instruction, src_arg,  false);
					setupMemsetValue(function, converted2, instruction, len_arg,  true);

					VariablePtr a0 = function.ax(0, instruction),
					            a1 = function.ax(1, instruction),
					            a2 = function.ax(2, instruction);

					auto push0 = std::make_shared<StackPushInstruction>(a0);
					auto push1 = std::make_shared<StackPushInstruction>(a1);
					auto push2 = std::make_shared<StackPushInstruction>(a2);
					auto move0 = std::make_shared<MoveInstruction>(dest_arg, a0);
					auto move1 = std::make_shared<MoveInstruction>(src_arg, a1);
					auto move2 = std::make_shared<MoveInstruction>(len_arg, a2);
					auto jump  = std::make_shared<JumpInstruction>(StringSet::intern("memcpy"), true);
					auto pop2  = std::make_shared<StackPopInstruction>(a2);
					auto pop1  = std::make_shared<StackPopInstruction>(a1);
					auto pop0  = std::make_shared<StackPopInstruction>(a0);

					function.insertBefore(instruction, push0, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, push1, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, push2, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, move0, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, move1, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, move2, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, jump, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, pop2, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, pop1, false)->setDebug(llvm)->extract();
					function.insertBefore(instruction, pop0, false)->setDebug(llvm)->extract();

					to_remove.push_back(instruction);
					++iter;
					continue;
				} catch (const std::exception &err) {
					error() << "Failed to replace memcpy.p0i8.p0i8.i64 intrinsic: " << err.what() << "\n";
				}
			} else throw std::runtime_error("Unhandled memcpy intrinsic: " + name);
			++iter;
		}

		if (!to_remove.empty()) {
			for (InstructionPtr &instruction: to_remove)
				function.remove(instruction);
			function.reindexInstructions();
		}

		return replaced;
	}

	
}
