#pragma once

#include <concepts>
#include <format>
#include <mutex>

namespace LL2W {
	template <typename T>
	struct Lockable: T {
		using Base = T;

		mutable std::mutex mutex;

		using T::T;

		Lockable(const Lockable<T> &other): T(other.getBase()) {}
		Lockable(const T &other): T(other) {}

		/** Likely data race issue. */
		Lockable(Lockable<T> &&other) noexcept: T(std::move(other.getBase())) {}
		Lockable(T &&other) noexcept: T(std::move(other)) {}

		Lockable<T> & operator=(const Lockable<T> &other) {
			if (this == &other) {
				return *this;
			}
			auto this_lock = getLock();
			auto other_lock = other.getLock();
			T::operator=(other.getBase());
			return *this;
		}

		Lockable<T> & operator=(Lockable<T> &&other) noexcept {
			if (this == &other) {
				return *this;
			}
			auto this_lock = getLock();
			auto other_lock = other.getLock();
			T::operator=(std::move(other.getBase()));
			return *this;
		}

		template <typename U>
		Lockable<T> & operator=(const U &other) {
			auto lock = getLock();
			T::operator=(other);
			return *this;
		}

		template <typename U>
		Lockable<T> & operator=(U &&other) noexcept {
			auto lock = getLock();
			T::operator=(std::forward<U>(other));
			return *this;
		}

		template <typename U>
		Lockable<T> & unsafeSet(U &&other) {
			T::operator=(std::forward<U>(other));
			return *this;
		}

		inline auto getLock() const { return std::unique_lock(mutex); }
		inline auto tryLock() const { return std::unique_lock(mutex, std::try_to_lock); }

		inline T & getBase() { return static_cast<T &>(*this); }
		inline const T & getBase() const { return static_cast<const T &>(*this); }

		inline T & getBase(std::unique_lock<std::mutex> &lock) { lock = getLock(); return static_cast<T &>(*this); }
		inline const T & getBase(std::unique_lock<std::mutex> &lock) const { lock = getLock(); return static_cast<const T &>(*this); }

		template <typename Fn>
		requires std::invocable<Fn>
		decltype(auto) withLock(Fn &&function) const {
			auto lock = getLock();
			return function();
		}

		template <typename Fn>
		requires std::invocable<Fn, const T &>
		decltype(auto) withLock(Fn &&function) const {
			auto lock = getLock();
			return function(getBase());
		}

		template <typename Fn>
		requires (std::invocable<Fn, T &> && !std::invocable<Fn, const T &>)
		decltype(auto) withLock(Fn &&function) {
			auto lock = getLock();
			return function(getBase());
		}

		inline T copyBase() const {
			auto lock = getLock();
			return static_cast<T>(*this);
		}
	};
}

template <typename T>
struct std::formatter<LL2W::Lockable<T>> {
	constexpr auto parse(auto &ctx) {
		return ctx.begin();
	}

	auto format(const auto &lockable, auto &ctx) const {
		auto lock = lockable.getLock();
		return std::format_to(ctx.out(), "{}", lockable.getBase());
	}
};
