#ifndef INSTRUCTION_LABEL_H_
#define INSTRUCTION_LABEL_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct Label: public WhyInstruction {
		std::string name;

		Label(const std::string &name_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
		bool showDebug() const override { return false; }
	};
}

#endif
