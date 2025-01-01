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
	struct WeakSet: std::set<std::weak_ptr<T>, WeakCompare<T>> {
		using std::set<std::weak_ptr<T>, WeakCompare<T>>::set;

		template <typename F>
		bool iterate(F &&function) const {
			for (const std::weak_ptr<T> &weak: *this) {
				if (std::shared_ptr<T> strong = weak.lock()) {
					if (function(std::move(strong))) {
						return true;
					}
				}
			}

			return false;
		}

		void clean() const {
			std::erase_if(*this, [](const std::weak_ptr<T> &weak) {
				return weak.expired();
			});
		}

		template <typename F>
		void clean(F &&function) {
			std::erase_if(*this, [&function](const std::weak_ptr<T> &weak) {
				if (std::shared_ptr<T> strong = weak.lock()) {
					function(std::move(strong));
					return false;
				}

				return true;
			});
		}
	};

	template <typename K, typename V>
	using WeakMap = std::map<std::weak_ptr<K>, V, WeakCompare<K>>;
}
