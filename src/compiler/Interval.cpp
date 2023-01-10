#include <cassert>
#include <iostream>
#include <algorithm>

#include "compiler/BasicBlock.h"
#include "compiler/Interval.h"
#include "compiler/Variable.h"

namespace LL2W {
	Interval::Interval(const VariablePtr &var): variable(var) {
		firstDefinition = *std::min_element(var->definingBlocks.begin(), var->definingBlocks.end(),
			[](const auto &left, const auto &right) {
				return left.lock()->index < right.lock()->index;
			});
		auto last_use_iter = std::max_element(var->usingBlocks.begin(), var->usingBlocks.end(),
			[](const auto &left, const auto &right) {
				return left.lock()->index < right.lock()->index;
			});
		// Some variables have no uses. For these variables, we consider the defining block to be the last user.
		lastUse = last_use_iter == var->usingBlocks.end()? firstDefinition : *last_use_iter;
	}

	int Interval::startpoint() const {
		if (auto locked = firstDefinition.lock())
			return locked->index;
		error() << "Interval for variable ";
		if (auto locked = variable.lock())
			std::cerr << *locked;
		else
			std::cerr << "(null)";
		std::cerr << " has no first definition.\n";
		throw std::logic_error("Can't find interval startpoint");
	}

	int Interval::endpoint() const {
		if (auto locked = lastUse.lock())
			return locked->index;
		error() << "Interval for variable ";
		if (auto locked = variable.lock())
			std::cerr << *locked;
		else
			std::cerr << "(null)";
		std::cerr << " has no last use.\n";
		throw std::logic_error("Can't find interval last use");
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
			return locked->plainString() + "[" + std::to_string(startpoint()) + ", " + std::to_string(endpoint()) + "]";
		return "nullptr[" + std::to_string(startpoint()) + ", " + std::to_string(endpoint()) + "]";
	}

	std::ostream & operator<<(std::ostream &os, const Interval &interval) {
		return os << std::string(interval);
	}
}