#pragma once

#include <memory>
#include <string>
#include <variant>

namespace LL2W {
	class Variable;
	using Immediate = std::variant<int, char, const std::string *>;
	std::string colorize(const Immediate &, bool ampersand = false);
	std::string colorize(const Immediate &, const Variable &, bool ampersand = false);
	std::string colorize(const Immediate &, const Variable &, int pointer_diff);
	std::string toString(const Immediate &, bool ampersand = false);
	std::string toString(const Immediate &, const Variable &, bool ampersand = false);
	std::string toString(const Immediate &, const Variable &, int pointer_diff);
}
