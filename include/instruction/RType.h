#ifndef INSTRUCTION_RTYPE_H_
#define INSTRUCTION_RTYPE_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	class RType: public WhyInstruction {
		protected:
			using VariablePtr = std::shared_ptr<Variable>;
			std::string operDebug(const char *) const;
			std::string operString(const char *) const;

		public:
			VariablePtr rs, rt, rd;

			RType(VariablePtr rs_, VariablePtr rt_, VariablePtr rd_, int index_ = -1);

			ExtractionResult extract(bool force = false) override;
			bool replaceRead(VariablePtr, VariablePtr) override;
	};
}

#endif
