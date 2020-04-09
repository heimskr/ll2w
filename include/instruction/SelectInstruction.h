#ifndef INSTRUCTION_SELECTINSTRUCTION_H_
#define INSTRUCTION_SELECTINSTRUCTION_H_

#include <unordered_map>

#include "instruction/RType.h"

namespace LL2W {
	class SelectInstruction: public RType {
		private:
			static const std::unordered_map<Condition, const char *> operMap;

		public:
			Condition condition;

			SelectInstruction(VariablePtr rs_, VariablePtr rt_, VariablePtr rd_, Condition condition_, int index_ = -1);
			std::string debugExtra() override;
			std::string toString() const override;
	};
}

#endif
