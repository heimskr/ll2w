#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/SplIInstruction.h"
#include "instruction/SpsIInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "instruction/SubIInstruction.h"
#include "pass/LowerStack.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	static int getOffset(const Function &function, const StackLocation &location) {
		int offset = location.offset;
		if (location.purpose != StackLocation::Purpose::Spill) {
			offset += function.spillSize + 8; // TODO: verify "+ 8"
		}
		return offset;
	}

	int lowerStack(Function &function) {
		// TODO!: verify sizes throughout this pass
		Timer timer{"LowerStack"};
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			if (auto *stack_store = dynamic_cast<StackStoreInstruction *>(instruction.get())) {
				const int offset = getOffset(function, stack_store->location);
				std::string plain_string = stack_store->location.variable->plainString();
				if (offset == 0) {
					// %var -> [$fp]
					VariablePtr fp = function.fp(function.getEntry());
					auto store = std::make_shared<StoreRInstruction>(stack_store->variable, std::move(fp), WASMSize::Word);
					std::string comment = "LowerStack: " + std::move(plain_string) + " -> [$fp]";
					function.insertBefore(instruction, std::move(store), std::move(comment))->setDebug(stack_store)->extract();
				} else {
					auto sps = std::make_shared<SpsIInstruction>(offset, stack_store->variable);
					std::string comment = "LowerStack: " + std::move(plain_string) + " -> [$fp - " + std::to_string(offset) + ']';
					function.insertBefore(instruction, std::move(sps), std::move(comment))->setDebug(stack_store)->extract();
				}
			} else if (auto *stack_load = dynamic_cast<StackLoadInstruction *>(instruction.get())) {
				const int offset = getOffset(function, stack_load->location);
				std::string plain_string = stack_load->location.variable->plainString();
				if (offset == 0) {
					// [$fp] -> %var
					VariablePtr fp = function.fp(function.getEntry());
					auto load = std::make_shared<LoadRInstruction>(std::move(fp), stack_load->result, WASMSize::Word);
					std::string comment = "LowerStack: [$fp] -> " + std::move(plain_string);
					function.insertBefore(instruction, std::move(load), std::move(comment))->setDebug(stack_load)->extract();
				} else {
					auto spl = std::make_shared<SplIInstruction>(offset, stack_load->result);
					std::string comment = "LowerStack: [$fp - " + std::to_string(offset) + "] -> " + std::move(plain_string);
					function.insertBefore(instruction, std::move(spl), std::move(comment))->setDebug(stack_load)->extract();
				}
			} else {
				continue;
			}

			to_remove.push_back(instruction);
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return to_remove.size();
	}
}
