#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/ReplaceConstants.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void replaceConstants(Function &function) {
		for (InstructionPtr &instruction: function.linearInstructions) {
			std::shared_ptr<LLVMInstruction> llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->node->nodeType() == NodeType::Call)
				continue;

			Reader *reader = dynamic_cast<Reader *>(llvm->node);
			if (!reader)
				continue;

			for (ConstantPtr constant: reader->allConstants())
				if (constant->conversion == Conversion::Bitcast) {
					constant->type = constant->conversionType;
					constant->value = constant->conversionSource->value;
					constant->conversion = Conversion::None;
				}

			for (ValuePtr *value: reader->allValuePointers()) {
				GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value->get());
				if (!gep)
					continue;
				std::cerr << "gep: " << *gep << "\n";
				std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
				if (!gep_global) {
					warn() << "Not sure what to do when the argument of getelementptr isn't a global.\n";
					function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
				} else {
					TypePtr out_type;
					const int offset = Util::updiv(Getelementptr::compute(gep, &out_type), 8);
					TypePtr ptr_type = std::make_shared<PointerType>(out_type);
					VariablePtr new_var = function.newVariable(ptr_type, instruction->parent.lock());
					auto setsym = std::make_shared<SetInstruction>(new_var, gep_global->name);
					function.insertBefore(instruction, setsym)->setDebug(*llvm)->extract();
					if (offset != 0) {
						auto addi = std::make_shared<AddIInstruction>(new_var, offset, new_var);
						function.insertAfter(setsym, addi)->setDebug(*llvm)->extract();
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
