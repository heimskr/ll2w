#pragma once

#include "compiler/WhyInfo.h"
#include "instruction/IntermediateInstruction.h"
#include "util/Makeable.h"

namespace LL2W {
	struct SemiUnclobber;
	struct Unclobber;

	struct Clobber: IntermediateInstruction, Makeable<Clobber> {
		int reg;
		std::shared_ptr<Unclobber> unclobber;
		std::vector<std::shared_ptr<SemiUnclobber>> semis;

		Clobber(int reg_, int index_ = -1):
			IntermediateInstruction(index_), reg(reg_) {}

		std::string debugExtra() const override { return toString(); }

		std::string toString() const override {
			return "\e[33mclobber\e[32m $" + WhyInfo::registerName(reg) + " \e[39m";
		}

		bool maySpill() const override { return false; }

		std::shared_ptr<SemiUnclobber> makeSemi(const VariablePtr &destination);
		Instruction * copy() const override {
			// TODO: do we also copy unclobber and semis?
			return new Clobber(reg);
		}
	};

	/** Ideally not to be instantiated directly—use Function::unclobber instead. */
	struct Unclobber: IntermediateInstruction, Makeable<Unclobber> {
		int reg;

		Unclobber(int reg_, int index_ = -1):
			IntermediateInstruction(index_), reg(reg_) {}

		std::string debugExtra() const override { return toString(); }

		std::string toString() const override {
			return "\e[33munclobber\e[32m $" + WhyInfo::registerName(reg) + "\e[39m";
		}

		bool maySpill() const override { return false; }

		std::pair<int, int> extractPrecolored() override {
			precoloredWritten = {reg};
			return {0, 1};
		}

		Instruction * copy() const override { return new Unclobber(reg, index); }
	};

	struct SemiUnclobber: IntermediateInstruction, Makeable<SemiUnclobber> {
		int reg;
		VariablePtr source;
		VariablePtr destination;

		SemiUnclobber(int reg_, VariablePtr source_, VariablePtr destination_, int index_ = -1):
			IntermediateInstruction(index_),
			reg(reg_),
			source(std::move(source_)),
			destination(std::move(destination_)) {}

		std::string debugExtra() const override { return toString(); }
		std::string toString() const override;

		ExtractionResult extract(bool force) override;

		std::pair<int, int> extractPrecolored() override;

		Instruction * copy() const override { return new SemiUnclobber(reg, source, destination, index); }
	};
}
