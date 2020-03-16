#ifndef INSTRUCTION_INVALIDINSTRUCTION_H_
#define INSTRUCTION_INVALIDINSTRUCTION_H_

#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	struct InvalidInstruction: public IntermediateInstruction {
		std::string message;
		InvalidInstruction(const std::string &message_ = "INVALID", int index_ = -1):
			IntermediateInstruction(index_), message(message_) {}
		std::string debugExtra() override { return "\e[41;97;1m " + message + " \e[39;49;22m"; }
		bool maySpill() const override { return false; }
	};
}

#endif
