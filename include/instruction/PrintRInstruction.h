#pragma once

#include "instruction/RType.h"
#include "parser/Enums.h"

namespace LL2W {
	class PrintRInstruction: public RType {
		public:
			PrintType type;

			PrintRInstruction(VariablePtr rs_, PrintType, int index_ = -1);
			std::string debugExtra() const override;
			std::string toString() const override;
			Instruction * copy() const override;

		private:
			const char * typeName() const;
	};
}
