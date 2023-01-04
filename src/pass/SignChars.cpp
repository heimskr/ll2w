#include "compiler/Function.h"
#include "pass/SignChars.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void signChars(Function &function) {
		Timer timer("SignChars");
		for (const auto &[var_id, var]: function.variableStore) {
			if (!var->type)
				continue;
			TypePtr type = var->type;
			while (type->isPointer())
				type = std::dynamic_pointer_cast<PointerType>(type)->subtype;
			if (type->isInt(8)) {
				auto int_type = std::dynamic_pointer_cast<IntType>(type);
				if (int_type->getSignedness() == Signedness::Unknown)
					int_type->setSignedness(Signedness::Unsigned);
			}
		}
	}
}
