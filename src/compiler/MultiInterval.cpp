#include <sstream>

#include "compiler/MultiInterval.h"
#include "compiler/Variable.h"

namespace LL2W {
	int MultiInterval::setRegister(int new_reg) {
		if (variable.lock())
			variable.lock()->setRegister(new_reg);
		return reg = new_reg;
	}

	bool MultiInterval::contains(int index) const {
		for (const Range &range: ranges) {
			if (index < range.first)
				return false;
			if (range.first <= index && index <= range.second)
				return true;
		}
		return false;
	}

	MultiInterval & MultiInterval::operator+=(const Range &add) {
		if (add.first > add.second)
			throw std::runtime_error("Start of range is after end of range (" + std::to_string(add.first) + " > "
				+ std::to_string(add.second) + ")");
		if (add.first == add.second)
			throw std::runtime_error("Range is empty (" + std::to_string(add.first) + ")");
		
		// First, try to extend existing ranges.
		for (Range &range: ranges) {
			//   .....   range  is contained within
			// ......... add
			if (add.first <= range.first && range.second <= add.second) {
				range = add;
				return *this;
			}

			// .....    range  extends before
			//    ..... add
			if (range.first <= add.first && add.first <= range.second && range.second < add.second) {
				range.second = add.second;
				return *this;
			}

			//    ..... range  extends past
			// .....    add
			if (add.first < range.first && range.first <= add.second && add.second <= range.second) {
				range.first = add.first;
				return *this;
			}

			// ......... range  contains
			//   .....   add
			if (range.first <= add.first && add.second <= range.second) {
				// No adjustments or additions are necessary.
				return *this;
			}
		}

		// If no existing range could be modified, add the range to the list of ranges.
		std::list<Range>::iterator iter, end = ranges.end();
		for (iter = ranges.begin(); iter != end && add.first < iter->first; ++iter);
		ranges.insert(iter, add);

		return *this;
	}

	MultiInterval::operator std::string() const {
		std::stringstream out;
		out << *variable.lock();
		for (const Range &range: ranges)
			out << " [" << range.first << ", " << range.second << "]";
		return out.str();
	}

	std::ostream & operator<<(std::ostream &os, const MultiInterval &interval) {
		return os << std::string(interval);
	}
}
