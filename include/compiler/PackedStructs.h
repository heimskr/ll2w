#pragma once

#include <memory>
#include <map>

#include "parser/Types.h"

namespace LL2W {

	class Function;
	class Instruction;
	class Variable;

	namespace PackedStructs {
		/** Inserts instructions to extract a value from a struct packed inside registers. */
		std::shared_ptr<Variable> extract(std::shared_ptr<Variable>, int index, Function &,
			std::shared_ptr<Instruction>);
	}
}
