#pragma once

#include "util/strnatcmp.h"
#include "util/WeakCompare.h"

#include <llvm/IR/User.h>
#include <llvm/Support/raw_os_ostream.h>

#include <algorithm>
#include <array>
#include <charconv>
#include <initializer_list>
#include <iostream>
#include <set>
#include <signal.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

int strnatcmp(const std::string &left, const std::string &right);
int strnatcmp(const std::string *left, const std::string *right);
int strnatcasecmp(const std::string &left, const std::string &right);
int strnatcasecmp(const std::string *left, const std::string *right);

namespace LL2W::Util {
	long parseLong(const std::string &, int base = 10);
	long parseLong(const std::string *, int base = 10);
	long parseLong(const char *, int base = 10);

	std::string getExecutablePath();
	std::string readAll(std::string_view command);
	std::vector<std::string> getBacktrace();
	std::string translateBacktrace(const std::vector<std::string> &);

	template <typename T>
	inline T upalign(T num, long alignment) {
		return num + ((alignment - (num % alignment)) % alignment);
	}

	template <typename T>
	inline T alignToPower(T num) {
		num--;
		for (size_t i = 1; i < 8 * sizeof(T); ++i) {
			num |= num >> i;
		}
		return num + 1;
	}

	bool isNumeric(const std::string &);
	bool isNumeric(const std::string *);
	bool isNumeric(std::string_view);
	bool isNumeric(const char *);

	bool isHex(const char);

	/** Returns true if the argument is lower than INT_MIN or higher than INT_MAX. */
	bool outOfRange(long);

	std::vector<std::string> split(const std::string &str, const std::string &delimiter, bool condense = true);

	std::string escape(const std::string &);

	template <template <typename...> typename C, typename T, typename D>
	std::string join(const C<T> &container, D &&delimiter) {
		std::stringstream ss;
		bool first = true;
		for (const T &item: container) {
			if (first) {
				first = false;
			} else {
				ss << delimiter;
			}
			ss << item;
		}
		return ss.str();
	}

	template <typename T>
	std::string hex(T n) {
		std::stringstream ss;
		ss << std::hex << n;
		return ss.str();
	}

	template <typename T>
	inline T updiv(T n, std::type_identity_t<T> d) {
		return n / d + (n % d? 1 : 0);
	}

	template <typename T, typename S>
	bool isAny(const T &thing, std::initializer_list<S> list) {
		for (const S &other: list) {
			if (thing == other) {
				return true;
			}
		}
		return false;
	}

	/** Merges two sets. */
	template <typename S>
	S merge(const S &first, const S &second) {
		S out;
		for (const auto &item: first) {
			out.insert(item);
		}
		for (const auto &item: second) {
			out.insert(item);
		}
		return out;
	}

	/** Returns whether two sets have any items in common. */
	template <typename S>
	bool hasOverlap(const S &first, const S &second) {
		for (const auto &item: first) {
			if (second.contains(item)) {
				return true;
			}
		}
		return false;
	}

	/** Adds all items from one set into another. */
	template <typename D, typename S>
	void absorb(D &destination, const S &source) {
		for (const auto &item: source) {
			destination.insert(item);
		}
	}

	template <typename T, template <typename...> typename C>
	bool equal(const C<T> &first, const C<T> &second) {
		if (first.size() != second.size()) {
			return false;
		}
		for (const T &item: first) {
			if (!second.contains(item)) {
				return false;
			}
		}
		return true;
	}

	template <template <typename...> typename C, typename T, template <typename...> typename O = std::vector>
	auto nsort(const C<T> &container, const bool sensitive = true) {
		O<T> out(container.cbegin(), container.cend());
		if (sensitive) {
			std::sort(out.begin(), out.end(), [](const auto &a, const auto &b) {
				return strnatcmp(a, b) == -1;
			});
		} else {
			std::sort(out.begin(), out.end(), [](const auto &a, const auto &b) {
				return strnatcasecmp(a, b) == -1;
			});
		}

		return out;
	}

	template <typename C, typename F, std::enable_if_t<!std::is_same<F, bool>::value, int> = 0>
	auto nsort(const C &container, F get, const bool sensitive = true) {
		std::vector<typename C::value_type> out(container.begin(), container.end());
		if (sensitive) {
			std::sort(out.begin(), out.end(), [get](const auto &a, const auto &b) {
				return strnatcmp(get(a).c_str(), get(b).c_str()) == -1;
			});
		} else {
			std::sort(out.begin(), out.end(), [get](const auto &a, const auto &b) {
				return strnatcasecmp(get(a).c_str(), get(b).c_str()) == -1;
			});
		}

		return out;
	}

	template <typename M>
	std::vector<typename M::value_type> mapnsort(const M &map, const bool sensitive = true) {
		using pair_type = std::pair<std::string, typename M::mapped_type>;
		std::vector<pair_type> vec(map.begin(), map.end());
		if (sensitive) {
			std::sort(vec.begin(), vec.end(), [](const pair_type &a, const pair_type &b) {
				return strnatcmp(a.first.c_str(), b.first.c_str()) == -1;
			});
		} else {
			std::sort(vec.begin(), vec.end(), [](const pair_type &a, const pair_type &b) {
				return strnatcasecmp(a.first.c_str(), b.first.c_str()) == -1;
			});
		}

		// I don't think there's any other way to cast A<B<C, D>> to A<B<const C, D>>.
		return *reinterpret_cast<std::vector<typename M::value_type> *>(&vec);
	}

	template <typename C, typename N>
	bool contains(const C &container, const N &needle) {
		for (const auto &item: container) {
			if (item == needle) {
				return true;
			}
		}
		return false;
	}

	template <typename T>
	std::ostream & out(std::ostream &os, const std::unordered_set<T> &set) {
		bool first = true;
		for (const auto &item: set) {
			if (first) {
				first = false;
			} else {
				os << ' ';
			}
			os << item;
		}
		return os;
	}

	template <typename T>
	std::ostream & out(std::ostream &os, const std::set<T> &set) {
		bool first = true;
		for (const auto &item: set) {
			if (first) {
				first = false;
			} else {
				os << ' ';
			}
			os << item;
		}
		return os;
	}

	template <typename T>
	T parse(std::string_view string, int base = 10) {
		T out = 0;
		auto [ptr, err] = std::from_chars(string.data(), string.data() + string.length(), out, base);
		if (err == std::errc{}) {
			return out;
		}
		throw std::invalid_argument(std::format("Not an integer: \"{}\"", string));
	}

	template <typename T>
	void copyPointer(T &ptr) {
		if (ptr) {
			ptr = ptr->copy();
		}
	}

	// Credit for reverse: https://stackoverflow.com/a/28139075/227663

	template <typename T>
	concept Reversible = requires(T t) {
		t.rbegin();
		t.rend();
	};

	template <Reversible T>
	struct reverse {
		T &iterable;
		reverse() = delete;
		reverse(T &iterable_): iterable(iterable_) {}
	};

	template <Reversible T>
	auto begin(reverse<T> r) {
		return std::rbegin(r.iterable);
	}

	template <Reversible T>
	auto end(reverse<T> r) {
		return std::rend(r.iterable);
	}
}

namespace LL2W {
	inline std::ostream & warn(std::ostream &stream = std::cerr, bool with_text = true) {
		stream << "\e[2m[\e[22;33m!\e[39;2m]\e[22m ";
		if (with_text) {
			stream << "\e[33mWarning:\e[39m ";
		}
		return stream;
	}

	inline std::ostream & error(std::ostream &stream = std::cerr, bool with_text = true) {
		stream << "\e[2m[\e[22;31m!\e[39;2m]\e[22m ";
		if (with_text) {
			stream << "\e[31mError:\e[39m ";
		}
		return stream;
	}

	inline std::ostream & info(std::ostream &stream = std::cerr) {
		return stream << "\e[2m[\e[22;36mi\e[39;2m]\e[22m ";
	}

	inline std::ostream & success(std::ostream &stream = std::cerr) {
		return stream << "\e[2m[\e[22;32m🗸\e[39;2m]\e[22m ";
	}

	inline void debugger() {
		raise(SIGTRAP);
	}

	template <typename T>
	void dump(const T &item, std::ostream &os = std::cerr) {
		llvm::raw_os_ostream raw(os);
		item.print(raw);
		(raw << "\n").flush();
	}

	template <typename T>
	std::string getOperandName(const T &item) {
		std::string name;
		llvm::raw_string_ostream os(name);
		item.printAsOperand(os, false);
		return name;
	}

	void dump(const llvm::User::const_op_range &);
}
