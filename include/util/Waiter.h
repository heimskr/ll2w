#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>

namespace LL2W {
	/** Useful for when you want to wait for a certain number of jobs in a thread pool to finish. */
	class Waiter {
		public:
			Waiter(size_t remaining_) noexcept;

			Waiter & operator--() noexcept;
			size_t operator--(int) noexcept;
			void wait();
			bool isDone() const noexcept;
			void reset(size_t, bool force = false);
			inline auto getRemaining() const { return remaining.load(); }

		private:
			std::condition_variable condition;
			std::atomic_size_t remaining;
			std::mutex mutex;
	};
}
