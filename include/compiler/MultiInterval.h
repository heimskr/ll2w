#ifndef COMPILER_MULTIINTERVAL_H_
#define COMPILER_MULTIINTERVAL_H_

#include <list>
#include <memory>
#include <ostream>
#include <utility>

namespace LL2W {
	class Variable;

	class MultiInterval {
		public:
			using Range = std::pair<int, int>;

		private:
			std::list<Range> ranges;
			void insert(const Range &);

		public:
			std::weak_ptr<Variable> variable;
			int reg = -1;

			MultiInterval() = delete;
			MultiInterval(std::shared_ptr<Variable> variable_): variable(variable_) {}

			int setRegister(int);
			bool contains(int) const;
			bool overlaps(const MultiInterval &) const;
			void shortenFront(int);
			int startpoint() const;
			int endpoint() const;

			MultiInterval & operator+=(const Range &);
			operator std::string() const;
	};

	std::ostream & operator<<(std::ostream &, const MultiInterval &);
}

#endif
