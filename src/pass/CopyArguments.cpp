#include <iostream>

#include "compiler/Function.h"
#include "instruction/MoveInstruction.h"
#include "pass/CopyArguments.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void copyArguments(Function &function) {
		Timer timer("CopyArguments");

		if (function.getCallingConvention() != CallingConvention::Reg16 || function.isNaked())
			return;

		const int arity = function.getArity();
		BasicBlockPtr entry = function.getEntry();
		const int debug_index = function.initialDebugIndex;

		InstructionPtr first = function.firstInstruction(true);
		if (!first)
			throw std::runtime_error("Couldn't find a non-label instruction in the initial block of " + *function.name);

		for (int i = 0; i < arity; ++i) {
			VariablePtr source = function.ax(i, entry);
			VariablePtr destination = function.getVariable(std::to_string(i));
			if (!function.arguments)
				warn() << "Function " << *function.name << " has no arguments information.\n";
			else
				source->type = destination->type = function.arguments->at(i).type;
			auto move = std::make_shared<MoveInstruction>(source, destination);
			function.insertBefore(first, move, "CopyArguments: " + source->plainString() + " -> " +
				destination->plainString(), false)->setDebug(debug_index)->extract();
		}

		function.reindexInstructions();
	}
}
