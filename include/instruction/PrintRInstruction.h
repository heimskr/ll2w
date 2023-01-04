#pragma once

#include "instruction/RType.h"
#include "parser/Enums.h"

namespace LL2W {
	class PrintRInstruction: public RType {
		public:
			PrintType type;

			PrintRInstruction(VariablePtr rs_, PrintType, int index_ = -1);
			std::string debugExtra() override;
			std::string toString() const override;

		private:
			const char * typeName() const;
	};
}
