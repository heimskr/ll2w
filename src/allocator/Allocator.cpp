#include "allocator/Allocator.h"
#include "compiler/Function.h"
#include "compiler/Variable.h"
#include "exception/NoChoiceError.h"
#include "util/Timer.h"

// #define DEBUG_SELECTMOSTLIVE

namespace LL2W {
	VariablePtr Allocator::selectLowestSpillCost() const {
		VariablePtr ptr;
		int lowest = INT_MAX;
		for (const auto &[id, var]: function->variableStore) {
			if (var->allRegistersSpecial())
				continue;
			var->clearSpillCost();
			const int cost = var->spillCost();
			if (cost != -1 && !triedIDs.contains(var->id) && cost < lowest && !var->isSimple()) {
				lowest = cost;
				ptr = var;
			}
		}

		if (!ptr) {
			function->debug();
			throw NoChoiceError("Couldn't select lowest spill cost variable");
		}

		return ptr;
	}

	VariablePtr Allocator::selectMostLive(int *liveness_out) const {
		Timer timer("SelectMostLive");
		VariablePtr ptr;
		size_t highest = SIZE_MAX;
		for (const auto *map: {&function->variableStore, &function->extraVariables})
			for (const auto &[id, var]: *map) {
				if (var->allRegistersSpecial()) {
#ifdef DEBUG_SELECTMOSTLIVE
					std::cerr << "Skipping " << *var << ": all registers are special\n";
#endif
					continue;
				}

				if (!function->canSpill(var)) {
#ifdef DEBUG_SELECTMOSTLIVE
					std::cerr << "Skipping " << *var << ": can't spill\n";
#endif
					continue;
				}

				const size_t sum = function->getLiveIn(var).size() + function->getLiveOut(var).size();
				if (highest == SIZE_MAX || (highest < sum && !triedIDs.contains(var->originalID))) {
					highest = sum;
					ptr = var;
				}
			}

		if (!ptr) {
			function->debug();
			throw std::runtime_error("Couldn't select variable with highest liveness in function " + *function->name);
		}

		if (liveness_out != nullptr)
			*liveness_out = highest;

		if (!function->canSpill(ptr))
			warn() << "Impossibility detected: can't spill " << *ptr << "\n";

		return ptr;
	}
}