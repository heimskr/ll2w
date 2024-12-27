#pragma once

#include "compiler/LivePoint.h"

#include <functional>
#include <memory>
#include <ostream>
#include <set>

namespace LL2W {
	class Function;
	class Variable;

	class Interval {
		public:
			// std::weak_ptr<LivePoint> firstDefinition, lastUse;
			std::weak_ptr<Variable> variable;
			std::set<int> registers;

			Interval(Function &, const std::shared_ptr<Variable> &);
			int getStartpoint() const;
			int getEndpoint() const;

			std::set<int> & setRegisters(const std::set<int> &);
			void applyRegisters();
			size_t registersRequired() const;

			operator std::string() const;
			operator bool() const { return valid; }

		private:
			Function *function = nullptr;
			int startpoint = -1;
			int endpoint = -1;
			bool valid = true;

			std::optional<int> getFirst(Function &, const std::shared_ptr<Variable> &, LivePoint::SetPtr) const;
			int guess();
			int calculateStartpoint(Function &);
			int calculateEndpoint(Function &);
	};

	std::ostream & operator<<(std::ostream &, const Interval &);
}
