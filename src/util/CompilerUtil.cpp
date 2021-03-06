#include "util/CompilerUtil.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/WhyInstruction.h"
#include "parser/Nodes.h"

namespace LL2W::CompilerUtil {
	bool isTerminator(InstructionPtr instruction) {
		if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get())) {
			switch (llvm->node->nodeType()) {
				case NodeType::BrUncond: return true;
				case NodeType::BrCond: return true;
				case NodeType::Ret: return true;
				case NodeType::Switch: return true;
				case NodeType::Unreachable: return true;
				default: return false;
			}
		} else if (WhyInstruction *why = dynamic_cast<WhyInstruction *>(instruction.get())) {
			return why->alwaysTerminal();
		}

		return false;
	}

#define CAST_METHOD(type, fn_name) \
	type##Node * fn_name##Cast(InstructionPtr instruction) { \
		if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get())) { \
			if (llvm->node->nodeType() == NodeType::type) \
				return dynamic_cast<type##Node *>(llvm->node); \
		} \
		return nullptr; \
	}

	CAST_METHOD(BrUncond, brUncond)
	CAST_METHOD(BrCond, brCond)
	CAST_METHOD(Ret, ret)
	CAST_METHOD(Switch, switch)
	CAST_METHOD(Unreachable, unreachable)
}
