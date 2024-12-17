#include "util/CompilerUtil.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/WhyInstruction.h"
#include "parser/Nodes.h"

namespace LL2W::CompilerUtil {
	bool labelsMatch(std::string_view one, std::string_view two) {
		if (one.empty() || two.empty())
			return false;

		if (one.front() == '%')
			one.remove_prefix(1);

		if (two.front() == '%')
			two.remove_prefix(1);

		return one == two;
	}

#define CAST_METHOD(type, fn_name) \
	type##Node * fn_name##Cast(const InstructionPtr &instruction) { \
		if (LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get())) { \
			if (llvm->getNodeType() == NodeType::type) \
				return dynamic_cast<type##Node *>(llvm->getNode()); \
		} \
		return nullptr; \
	}

	CAST_METHOD(BrUncond, brUncond)
	CAST_METHOD(BrCond, brCond)
	CAST_METHOD(Ret, ret)
	CAST_METHOD(Switch, switch)
	CAST_METHOD(Unreachable, unreachable)
}
