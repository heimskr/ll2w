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
		lastUse = *std::max_element(var->definingBlocks.begin(), var->definingBlocks.end(),
			[&](const std::shared_ptr<BasicBlock> &left, const std::shared_ptr<BasicBlock> &right) {
				return left->label < right->label;
			});
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