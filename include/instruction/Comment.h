#ifndef INSTRUCTION_COMMENT_H_
#define INSTRUCTION_COMMENT_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct Comment: public WhyInstruction {
		std::string text;

		Comment(const std::string &text_, int index_ = -1);

		bool showDebug() const override { return false; }

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
