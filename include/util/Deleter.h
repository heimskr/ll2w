#pragma once

#include <iostream>
#include <vector>

template <typename T>
class Deleter {
	private:
		std::vector<T *> pointers;

	public:
		template <typename... Args>
		Deleter(T *first, Args &&...rest): pointers{first, rest...} {}
		Deleter(T *pointer): pointers{pointer} {}
		~Deleter() {
			for (T *pointer: pointers) {
				delete pointer;
			}
		}
};
