#ifndef UTIL_WEAKCOMPARE_H_
#define UTIL_WEAKCOMPARE_H_

#include <memory>

namespace LL2W {
	template <typename T>
	struct WeakCompare {
		bool operator()(std::weak_ptr<T> left, std::weak_ptr<T> right) const {
			std::shared_ptr<T> llock = left.lock(), rlock = right.lock();
			if (!rlock)
				return false;
			if (!llock)
				return true;
			return llock.get() < rlock.get();
		}
	};
}

#endif
