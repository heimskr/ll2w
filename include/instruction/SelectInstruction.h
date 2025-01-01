#pragma once

#include "instruction/RType.h"

#include <unordered_map>

namespace LL2W {
	class SelectInstruction: public RType {
		private:
			static const std::unordered_map<Condition, const char *> operMap;

		public:
			Condition condition;

			SelectInstruction(VariablePtr rs, VariablePtr rt, VariablePtr rd, Condition condition);
			std::string debugExtra() const override;
			std::string toString() const override;
			Instruction * copy() const override;
	};
}
