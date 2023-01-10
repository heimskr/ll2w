#pragma once

#include <chrono>
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace LL2W {
	class Timer {
		public:
			static std::map<std::string, std::chrono::nanoseconds> times;
			static std::map<std::string, size_t> counts;
			static std::mutex mutex;

			std::chrono::system_clock::time_point start;
			const std::string name;

			Timer(const std::string &name_);
			~Timer();

			std::chrono::nanoseconds difference() const;
			void stop();

			static void summary(double threshold = 0.0);

		private:
			bool stopped = false;
	};
}

extern "C" void timer_summary();
