#pragma once

#include <string>
#include <variant>

namespace LL2W {
	using Immediate = std::variant<int, const std::string *>;
	std::string colorize(const Immediate &);
	std::string toString(const Immediate &);
}
