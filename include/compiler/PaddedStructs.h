#pragma once

#include <memory>

#include "parser/Types.h"

namespace LL2W {
	class Function;
	class Instruction;
	class Variable;

	namespace PaddedStructs {
		/** Inserts instructions to extract a value from a struct packed inside registers. */
		std::shared_ptr<Variable> extract(std::shared_ptr<Variable>, int index, Function &,
			std::shared_ptr<Instruction>);

		/** Inserts instructions to insert a value into a struct packed inside registers. */
		std::shared_ptr<Variable> insert(std::shared_ptr<Variable>, int index, Function &,
			std::shared_ptr<Instruction>);
	}
}
