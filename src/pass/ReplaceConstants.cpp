#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/InvalidInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/LowerIcmp.h"
#include "pass/ReplaceConstants.h"
#include "util/Timer.h"
#include "util/Util.h"

namespace LL2W::Passes {
	void replaceConstants(Function &function) {
		Timer timer("ReplaceConstants");

		for (InstructionPtr &instruction: function.linearInstructions) {
			std::shared_ptr<LLVMInstruction> llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
			if (!llvm || llvm->getNodeType() == NodeType::Call) {
				continue;
			}

			Reader *reader = dynamic_cast<Reader *>(llvm->getNode());
			if (!reader) {
				continue;
			}

			for (ConstantPtr constant: reader->allConstants())
				if (constant->conversion == Conversion::Bitcast) {
					constant->type = constant->conversionType;
					constant->value = constant->conversionSource->value;
					constant->conversion = Conversion::None;
				}

			for (ValuePtr *value: reader->allValuePointers()) {
				if (auto *gep = dynamic_cast<GetelementptrValue *>(value->get())) {
					std::shared_ptr<GlobalValue> gep_global = std::dynamic_pointer_cast<GlobalValue>(gep->variable);
					if (!gep_global) {
						warn() << "Not sure what to do when the argument of getelementptr isn't a global in replaceConstants.\n" << *gep << '\n';
						function.insertBefore(instruction, std::make_shared<InvalidInstruction>());
					} else {
						TypePtr out_type;
						const long offset = Util::updiv(Getelementptr::compute(gep, &out_type), 8l);
						if (Util::outOfRange(offset)) {
							warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';
						}
						TypePtr ptr_type = std::make_shared<PointerType>(out_type);
						VariablePtr new_var = function.newVariable(ptr_type, instruction->parent.lock());
						auto setsym = std::make_shared<SetInstruction>(new_var, gep_global->name);
						function.insertBefore(instruction, setsym)->setDebug(*llvm)->extract();
						if (offset != 0) {
							auto addi = std::make_shared<AddIInstruction>(new_var, int(offset), new_var);
							function.insertAfter(setsym, addi)->setDebug(*llvm)->extract();
						}

						*value = LocalValue::make(new_var);
					}
				} else if (IcmpValue *icmp = dynamic_cast<IcmpValue *>(value->get())) {
					VariablePtr new_var = function.newVariable(IntType::make(8, false), instruction->parent.lock());
					auto icmp_node = std::make_unique<IcmpNode>(new_var, icmp->cond, icmp->left, icmp->right);
					lowerIcmp(function, instruction, icmp_node.get());
					*value = LocalValue::make(new_var);
				}
			}

			instruction->extract(true);
		}

		function.extractVariables();
	}
}
