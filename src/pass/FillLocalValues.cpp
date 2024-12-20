#include "compiler/Function.h"
#include "compiler/LLVMInstruction.h"
#include "pass/FillLocalValues.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void fillLocalValues(Function &function) {
		Timer timer("FillLocalValues");
		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm) {
				continue;
			}

			InstructionNode *node = llvm->getNode();

			if (Reader *reader = dynamic_cast<Reader *>(node)) {
				for (std::shared_ptr<LocalValue> value: reader->allLocals()) {
					value->variable = function.getVariable(*value->name);
				}
			}

			if (Writer *writer = dynamic_cast<Writer *>(node)) {
				if (writer->result) {
					writer->variable = function.getVariable(*writer->result);
				}
			}
		}
	}
}
