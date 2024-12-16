#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/RemoveUnreachable.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t removeUnreachable(Function &function) {
		Timer timer("RemoveUnreachable");
		std::list<decltype(function.linearInstructions)::iterator> to_remove;

		auto end = function.linearInstructions.end();
		for (auto iter = function.linearInstructions.begin(); iter != end; ++iter) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(iter->get());
			if (llvm && llvm->getNode()->nodeType() == NodeType::Unreachable) {
				to_remove.push_back(iter);
			}
		}

		for (auto &iter: to_remove) {
			function.linearInstructions.erase(iter);
		}

		return to_remove.size();
	}
}
