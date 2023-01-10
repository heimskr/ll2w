#include "compiler/BasicBlock.h"
#include "compiler/Function.h"
#include "compiler/Interval.h"
#include "compiler/Variable.h"
#include "util/Timer.h"

#include <cassert>
#include <iostream>
#include <algorithm>

namespace LL2W {
	Interval::Interval(Function &function_, const VariablePtr &var): variable(var) {
		Timer timer("Interval::Interval");
		function = &function_;
		startpoint = calculateStartpoint(function_);
		endpoint = calculateEndpoint(function_);

		// firstDefinition = *std::min_element(var->definingBlocks.begin(), var->definingBlocks.end(),
		// 	[](const auto &left, const auto &right) {
		// 		return left.lock()->index < right.lock()->index;
		// 	});
		// auto last_use_iter = std::max_element(var->usingBlocks.begin(), var->usingBlocks.end(),
		// 	[](const auto &left, const auto &right) {
		// 		return left.lock()->index < right.lock()->index;
		// 	});
		// // Some variables have no uses. For these variables, we consider the defining block to be the last user.
		// lastUse = last_use_iter == var->usingBlocks.end()? firstDefinition : *last_use_iter;
	}

	std::optional<int>
	Interval::getFirst(Function &function, const std::shared_ptr<Variable> &var, BasicBlock::LivePtr lptr) const {
		for (const auto &block: function.blocks)
			if ((block.get()->*lptr).contains(var))
				return block->index;
		return std::nullopt;
	}

	// int Interval::calculatePoint(Function &function, BlockLivePtr lptr, const std::function<int(int, int)> &fn) const {
	// 	auto locked = variable.lock();
	// 	assert(locked);
	// 	int out = getFirst(function, locked, lptr);
	// 	for (Variable *alias: locked->getAliases())
	// 		out = fn(out, getFirst(function, alias->shared_from_this(), lptr));
	// 	return out;
	// }

	int Interval::guess() {
		auto locked_var = variable.lock();
		assert(locked_var);
		if (locked_var->definingBlocks.empty()) {
			// Sometimes variables get spilled out of existence.
			valid = false;
			return -1;
		}
		auto locked_block = locked_var->definingBlocks.begin()->lock();
		assert(locked_block);
		return locked_block->index;
	}

	int Interval::calculateStartpoint(Function &function) {
		auto locked = variable.lock();
		assert(locked);
		constexpr static auto live_ptr = &BasicBlock::liveOut;
		int calc = getFirst(function, locked, live_ptr).value_or(INT_MAX);
		for (Variable *alias: locked->getAliases())
			calc = std::min(calc, getFirst(function, alias->shared_from_this(), live_ptr).value_or(INT_MAX));
		return calc != INT_MAX? calc : guess();
	}

	int Interval::calculateEndpoint(Function &function) {
		auto locked = variable.lock();
		assert(locked);
		constexpr static auto live_ptr = &BasicBlock::liveIn;
		int calc = getFirst(function, locked, live_ptr).value_or(INT_MIN);
		for (Variable *alias: locked->getAliases())
			calc = std::max(calc, getFirst(function, alias->shared_from_this(), live_ptr).value_or(INT_MIN));
		return calc != INT_MIN? calc : guess();
	}

	int Interval::getStartpoint() const {
		assert(startpoint != -1);
		return startpoint;
	}

	int Interval::getEndpoint() const {
		assert(endpoint != -1);
		return endpoint;
	}

	std::set<int> & Interval::setRegisters(const std::set<int> &new_registers) {
		if (auto locked = variable.lock())
			locked->setRegisters(new_registers);
		if (&registers != &new_registers)
			registers = new_registers;
		return registers;
	}

	void Interval::applyRegisters() {
		auto locked = variable.lock();
		assert(locked);
		locked->setRegisters(registers);
	}

	size_t Interval::registersRequired() const {
		auto locked = variable.lock();
		assert(locked);
		return locked->registersRequired();
	}

	Interval::operator std::string() const {
		if (auto locked = variable.lock())
			return locked->plainString() + "[" + std::to_string(startpoint) + ", " + std::to_string(endpoint) + "]";
		return "nullptr[" + std::to_string(startpoint) + ", " + std::to_string(endpoint) + "]";
	}

	std::ostream & operator<<(std::ostream &os, const Interval &interval) {
		return os << std::string(interval);
	}
}