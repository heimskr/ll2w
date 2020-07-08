#include <iostream>
#include <algorithm>

#include "compiler/BasicBlock.h"
#include "compiler/Interval.h"
#include "compiler/Variable.h"

namespace LL2W {
	Interval::Interval(VariablePtr var): variable(var) {
		firstDefinition = *std::min_element(var->definingBlocks.begin(), var->definingBlocks.end(),
			[&](const std::shared_ptr<BasicBlock> &left, const std::shared_ptr<BasicBlock> &right) {
				return left->index < right->index;
			});
		auto last_use_iter = std::max_element(var->usingBlocks.begin(), var->usingBlocks.end(),
			[&](const std::shared_ptr<BasicBlock> &left, const std::shared_ptr<BasicBlock> &right) {
				return left->index < right->index;
			});
		// Some variables have no uses. For these variables, we consider the defining block to be the last user.
		lastUse = last_use_iter == var->usingBlocks.end()? firstDefinition : *last_use_iter;
	}

	int Interval::startpoint() const {
		return firstDefinition->index;
	}

	int Interval::endpoint() const {
		return lastUse->index;
	}

	int Interval::setRegister(int new_reg) {
		if (variable)
			variable->setRegister(new_reg);
		return reg = new_reg;
	}

	Interval::operator std::string() const {
		return variable->plainString() + "[" + std::to_string(startpoint()) + ", " + std::to_string(endpoint()) + "]";
	}

	std::ostream & operator<<(std::ostream &os, const Interval &interval) {
		return os << std::string(interval);
	}
}