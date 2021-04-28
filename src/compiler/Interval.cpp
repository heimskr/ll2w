#include <iostream>
#include <algorithm>

#include "compiler/BasicBlock.h"
#include "compiler/Interval.h"
#include "compiler/Variable.h"

namespace LL2W {
	Interval::Interval(VariablePtr var): variable(var) {
		firstDefinition = *std::min_element(var->definingBlocks.begin(), var->definingBlocks.end(),
			[&](const std::weak_ptr<BasicBlock> &left, const std::weak_ptr<BasicBlock> &right) {
				return left.lock()->index < right.lock()->index;
			});
		auto last_use_iter = std::max_element(var->usingBlocks.begin(), var->usingBlocks.end(),
			[&](const std::weak_ptr<BasicBlock> &left, const std::weak_ptr<BasicBlock> &right) {
				return left.lock()->index < right.lock()->index;
			});
		// Some variables have no uses. For these variables, we consider the defining block to be the last user.
		lastUse = last_use_iter == var->usingBlocks.end()? firstDefinition : *last_use_iter;
	}

	int Interval::startpoint() const {
		return firstDefinition.lock()->index;
	}

	int Interval::endpoint() const {
		return lastUse.lock()->index;
	}

	std::set<int> & Interval::setRegisters(const std::set<int> &new_registers) {
		if (variable.lock())
			variable.lock()->setRegisters(new_registers);
		return registers = new_registers;
	}

	Interval::operator std::string() const {
		return variable.lock()->plainString() + "[" + std::to_string(startpoint()) + ", " + std::to_string(endpoint())
			+ "]";
	}

	std::ostream & operator<<(std::ostream &os, const Interval &interval) {
		return os << std::string(interval);
	}
}