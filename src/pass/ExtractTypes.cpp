#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/ExtractTypes.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	static DbgIntrinsicNode * getDbg(const InstructionPtr &instruction) {
		auto llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
		return llvm? dynamic_cast<DbgIntrinsicNode *>(llvm->node) : nullptr;
	}

	static bool isIntbang(const std::string &str) {
		if (str.size() < 2 || str.front() != '!')
			return false;
		for (size_t i = 1; i < str.size(); ++i)
			if (!std::isdigit(str[i]))
				return false;
		return true;
	}

	void extractTypes(Function &function) {
		Timer timer("ExtractTypes");

		std::list<InstructionPtr> to_remove;

		// First, attempt to glean information from calls to @llvm.dbg.value intrinsics.
		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto *dbg = getDbg(instruction)) {
				to_remove.push_back(instruction);
				if (dbg->type == DbgIntrinsicNode::Type::Value) {
					const std::string &first = *dbg->firstMetadata->lexerInfo;
					if (!isIntbang(first))
						throw std::invalid_argument("Not an intbang: \"" + first + '"');
					
				}
			}
		}

		// for (const auto &[var_id, var]: function.variableStore) {
		// 	info() << *function.name << ": \e[35m%" << *var_id << "\e[39m\n";
		// 	std::string pad(function.name->size() *0+2 + 2, ' ');
		// }

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
