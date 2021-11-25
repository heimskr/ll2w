#pragma once

template <typename T>
struct Makeable {
	template <typename... Args>
	static std::shared_ptr<T> make(Args &&...args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
};
