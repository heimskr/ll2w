#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/PaddedStructs.h"
#include "compiler/WhyInfo.h"
#include "instruction/SetInstruction.h"
#include "parser/StructNode.h"
#include "pass/LowerExtractvalue.h"
#include "util/Timer.h"
#include "util/Util.h"

namespace LL2W::Passes {
	size_t lowerExtractvalue(Function &function) {
		Timer timer("LowerExtractvalue");
		size_t changed = 0;
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::ExtractValue)
				continue;
			ExtractValueNode *ev = dynamic_cast<ExtractValueNode *>(llvm->node);

			ValueType aggregate_type = ev->aggregateValue->valueType();

			if (aggregate_type == ValueType::Undef) {
				function.insertBefore(instruction, SetInstruction::make(ev->variable, 0), "ExtractValue: undef == 0")
					->setDebug(ev)->extract();
				to_remove.push_back(instruction);
				++changed;
				continue;
			}

			if (ev->decimals.size() != 1 || aggregate_type != ValueType::Local) {
				warn() << "Skipping unsupported extractvalue node: " << ev->debugExtra() << '\n';
				continue;
			}

			LocalValue *local = dynamic_cast<LocalValue *>(ev->aggregateValue.get());

			if (!local->variable->type) {
				warn() << "Variable " << *local->variable << " has no type.\n";
				continue;
			}

			if (local->variable->type->typeType() != TypeType::Struct) {
				warn() << "Type of variable " << *local->variable << " (" << *local->variable->type
				       << ") isn't Struct.\n";
				continue;
			}

			auto result = PaddedStructs::extract(local->variable, ev->decimals.front(), function, instruction);
			to_remove.push_back(instruction);
			++changed;
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return changed;
	}

	
}
