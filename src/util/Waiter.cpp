#include "util/Waiter.h"

namespace LL2W {
	Waiter::Waiter(size_t remaining_) noexcept:
		remaining(remaining_) {}

	Waiter & Waiter::operator--() noexcept {
		if (--remaining == 0) {
			condition.notify_all();
		}
		return *this;
	}

	size_t Waiter::operator--(int) noexcept {
		size_t out = --remaining;
		if (out == 0) {
			condition.notify_all();
		}
		return out;
	}

	void Waiter::wait() {
		std::unique_lock lock(mutex);
		if (remaining > 0) {
			condition.wait(lock, [this] { return remaining == 0; });
		}
	}

	bool Waiter::isDone() const noexcept {
		return remaining == 0;
	}

	void Waiter::reset(size_t new_remaining, bool force) {
		if (remaining.exchange(new_remaining) != 0 && !force)
			throw std::runtime_error("Reset an unfinished Waiter");
	}
}
