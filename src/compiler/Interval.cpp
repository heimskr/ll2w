#include <iostream>
#include <algorithm>

#include "compiler/BasicBlock.h"
#include "compiler/Interval.h"
#include "compiler/Variable.h"

namespace LL2W {
	Interval::Interval(VariablePtr var): variable(var) {
		firstDefinition = *std::min_element(var->definingBlocks.begin(), var->definingBlocks.end(),
			[&](const std::shared_ptr<BasicBlock> &left, const std::shared_ptr<BasicBlock> &right) {
				return left->label < right->label;
			});
		auto last_use_iter = std::max_element(var->usingBlocks.begin(), var->usingBlocks.end(),
			[&](const std::shared_ptr<BasicBlock> &left, const std::shared_ptr<BasicBlock> &right) {
				return left->label < right->label;
			});
		// Some variables have no uses. For these variables, we consider the defining block to be the last user.
		lastUse = last_use_iter == var->usingBlocks.end()? firstDefinition : *last_use_iter;
	}

	int Interval::startpoint() const {
		return firstDefinition->label;
	}

	int Interval::endpoint() const {
		return lastUse->label;
	}

	int Interval::setRegister(int new_reg) {
		if (variable)
			variable->setRegister(new_reg);
		return reg = new_reg;
	}
}