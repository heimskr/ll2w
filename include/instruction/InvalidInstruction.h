#pragma once

#include "instruction/IntermediateInstruction.h"
#include "util/Makeable.h"

namespace LL2W {
	struct InvalidInstruction: IntermediateInstruction, Makeable<InvalidInstruction> {
		std::string message;
		InvalidInstruction(const std::string &message_ = "INVALID", int index_ = -1):
			IntermediateInstruction(index_), message(message_) {}
		std::string debugExtra() override { return toString(); }
		std::string toString() const override { return "\e[41;97;1m " + message + " \e[39;49;22m"; }
		bool maySpill() const override { return false; }
		Instruction * copy() const override { return new InvalidInstruction(*this); }
	};
}
