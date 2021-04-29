#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/PackedStructs.h"
#include "compiler/WhyInfo.h"
#include "instruction/SetInstruction.h"
#include "parser/StructNode.h"
#include "pass/LowerExtractvalue.h"
#include "util/Util.h"

namespace LL2W::Passes {
	int lowerExtractvalue(Function &function) {
		int changed = 0;

		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::ExtractValue)
				continue;

			ExtractValueNode *ev = dynamic_cast<ExtractValueNode *>(llvm->node);

			if (ev->decimals.size() != 1 || ev->aggregateValue->valueType() != ValueType::Local)
				continue;

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

			StructType *struct_type = dynamic_cast<StructType *>(local->variable->type.get());

			auto padded = struct_type->pad();

			// for (const std::pair<const int, int> &pair: padded->paddingMap)
			// 	std::cerr << pair.first << " => " << pair.second << "\n";

			auto result = PackedStructs::extract(local->variable, ev->decimals.front(), function, instruction);
			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return changed;
	}
}