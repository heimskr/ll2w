#include "compiler/BasicBlock.h"
#include "compiler/Function.h"
#include "compiler/Interval.h"
#include "compiler/Variable.h"
#include "util/Timer.h"

#include <cassert>
#include <iostream>
#include <algorithm>

namespace LL2W {
	Interval::Interval(const VariablePtr &var): variable(var) {
		Timer timer("Interval::Interval");
		auto *function = var->getFunction();
		assert(function);
		startpoint = calculateStartpoint(*function);
		endpoint = calculateEndpoint(*function);

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

	int Interval::getFirst(Function &function, const std::shared_ptr<Variable> &var, BlockLivePtr lptr) const {
		for (const auto &block: function.blocks)
			if ((block.get()->*lptr).contains(var))
				return block->index;
		return INT_MAX;
	}

	int Interval::calculatePoint(Function &function, BlockLivePtr lptr) const {
		auto locked = variable.lock();
		assert(locked);
		int out = getFirst(function, locked, lptr);
		for (Variable *alias: locked->getAliases())
			out = std::min(out, getFirst(function, alias->shared_from_this(), lptr));
		return out;
	}

	int Interval::guess() const {
		auto locked_var = variable.lock();
		assert(locked_var);
		assert(locked_var->definingBlocks.size() == 1);
		auto locked_block = locked_var->definingBlocks.begin()->lock();
		assert(locked_block);
		return locked_block->index;
	}

	int Interval::calculateStartpoint(Function &function) const {
		if (const int calculated = calculatePoint(function, &BasicBlock::liveIn); calculated != INT_MAX)
			return calculated;
		return guess();
	}

	int Interval::calculateEndpoint(Function &function) const {
		if (const int calculated = calculatePoint(function, &BasicBlock::liveOut); calculated != INT_MAX)
			return calculated;
		return guess();
	}

	int Interval::getStartpoint() const {
		assert(startpoint != -1);
		return endpoint;
		// if (auto locked = firstDefinition.lock())
		// 	return locked->index;
		// error() << "Interval for variable ";
		// if (auto locked = variable.lock())
		// 	std::cerr << *locked;
		// else
		// 	std::cerr << "(null)";
		// std::cerr << " has no first definition.\n";
		// throw std::logic_error("Can't find interval startpoint");
	}

	int Interval::getEndpoint() const {
		assert(endpoint != -1);
		return endpoint;
		// if (auto locked = lastUse.lock())
		// 	return locked->index;
		// error() << "Interval for variable ";
		// if (auto locked = variable.lock())
		// 	std::cerr << *locked;
		// else
		// 	std::cerr << "(null)";
		// std::cerr << " has no last use.\n";
		// throw std::logic_error("Can't find interval last use");
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