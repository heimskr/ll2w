#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "pass/ExtractTypes.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void extractTypes(Function &function) {
		Timer timer("ExtractTypes");

		for (const auto &[var_id, var]: function.variableStore) {
			info() << *function.name << ": \e[35m%" << *var_id << "\e[39m\n";
			std::string pad(function.name->size() *0+2 + 2, ' ');
			for (const auto &weak_def: var->definitions) {
				auto def = weak_def.lock();
				info() << pad << "Def: " << def->debugExtra() << " -> " << def->debugIndex << '\n';
			}
			for (const auto &weak_use: var->uses) {
				auto use = weak_use.lock();
				info() << pad << "Use: " << use->debugExtra() << " -> " << use->debugIndex << '\n';
			}
		}
	}
}
