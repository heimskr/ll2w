#pragma once

#include <map>
#include <memory>
#include <set>

namespace LL2W {
	template <typename T>
	struct WeakCompare {
		bool operator()(std::weak_ptr<T> left, std::weak_ptr<T> right) const {
			std::shared_ptr<T> llock = left.lock();
			std::shared_ptr<T> rlock = right.lock();
			if (llock == rlock || !rlock) {
				return false;
			}
			if (!llock) {
				return true;
			}
			return llock.get() < rlock.get();
		}
	};

	template <typename T>
	using WeakSet = std::set<std::weak_ptr<T>, WeakCompare<T>>;

	template <typename K, typename V>
	using WeakMap = std::map<std::weak_ptr<K>, V, WeakCompare<K>>;
}
