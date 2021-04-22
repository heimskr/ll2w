#include "compiler/Immediate.h"

namespace LL2W {
	std::string colorize(const Immediate &imm) {
		if (std::holds_alternative<int>(imm))
			return "\e[32m" + std::to_string(std::get<int>(imm)) + "\e[39m";
		return "\e[38;5;202m" + *std::get<const std::string *>(imm) + "\e[39m";
	}

	std::string toString(const Immediate &imm) {
		if (std::holds_alternative<int>(imm))
			return std::to_string(std::get<int>(imm));
		return *std::get<const std::string *>(imm);
	}
}
