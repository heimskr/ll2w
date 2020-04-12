#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/SetSymbolInstruction.h"
#include "pass/ReplaceGetelementptrConstants.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void replaceGetelementptrConstants(Function &function) {
		for (InstructionPtr &instruction: function.linearInstructions) {
			std::shared_ptr<LLVMInstruction> llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->node->nodeType() == NodeType::Call)
				continue;

			Reader *reader = dynamic_cast<Reader *>(llvm->node);
			if (!reader)
				continue;

			for (ValuePtr *value: reader->allValuePointers()) {
				GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value->get());
				if (!gep)
					continue;
				std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
				if (!gep_global) {
					warn() << "Not sure what to do when the argument of getelementptr isn't a global.\n";
					function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
				} else {
					std::list<int> indices;
					for (const std::pair<int, long> &decimal_pair: gep->decimals)
						indices.push_back(decimal_pair.second);
					TypePtr out_type;
					const int offset = updiv(Getelementptr::compute(gep->ptrType, indices, &out_type), 8);
					VariablePtr new_var = function.newVariable(out_type, instruction->parent.lock());
					auto setsym = std::make_shared<SetSymbolInstruction>(new_var, *gep_global->name);
					function.insertBefore(instruction, setsym);
					setsym->extract();
					if (offset != 0) {
						auto addi   = std::make_shared<AddIInstruction>(new_var, offset, new_var);
						function.insertAfter(setsym, addi);
						addi->extract();
					}

					auto new_value = std::make_shared<LocalValue>(std::to_string(new_var->id));
					new_value->variable = new_var;
					*value = new_value;
				}
			}

			instruction->extract(true);
		}

		function.extractVariables();
	}
}
