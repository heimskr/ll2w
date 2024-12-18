#include "compiler/Immediate.h"
#include "compiler/Variable.h"

namespace LL2W {
	static TypePtr unwrap(TypePtr type, int pointer_diff) {
		if (pointer_diff < 0)
			for (int i = 0; i < -pointer_diff; ++i) {
				if (auto pointer_type = std::dynamic_pointer_cast<PointerType>(type))
					type = pointer_type->subtype;
				else
					throw std::runtime_error("Couldn't unwrap non-pointer type");
			}
		else if (0 < pointer_diff)
			for (int i = 0; i < pointer_diff; ++i)
				type = PointerType::make(type);

		return type;
	}

	std::string colorize(const Immediate &imm, bool ampersand) {
		if (std::holds_alternative<int>(imm))
			return "\e[32m" + std::to_string(std::get<int>(imm)) + "\e[39m";
		if (std::holds_alternative<char>(imm))
			return "\e[33m" + toString(imm, ampersand) + "\e[39m";
		if (ampersand)
			return "\e[38;5;202m&" + *std::get<const std::string *>(imm) + "\e[39m";
		return "\e[38;5;202m" + *std::get<const std::string *>(imm) + "\e[39m";
	}

	std::string colorize(const Immediate &imm, const Variable &var, bool ampersand) {
		std::string out = colorize(imm, ampersand);
		if (var.type == nullptr) {
			out += "{v}";
		} else {
			out += '{';
			out += var.type->whyString();
			out += '}';
		}
		return out;
	}

	std::string colorize(const Immediate &imm, const Variable &var, int pointer_diff) {
		std::string out = colorize(imm, false);
		if (var.type == nullptr) {
			out += "{v}";
		} else {
			out += '{';
			out += unwrap(var.type, pointer_diff)->whyString();
			out += '}';
		}
		return out;
	}

	std::string toString(const Immediate &imm, bool ampersand) {
		if (std::holds_alternative<int>(imm))
			return std::to_string(std::get<int>(imm));
		if (std::holds_alternative<char>(imm)) {
			char ch = std::get<char>(imm);
			switch (ch) {
				case '\n': return "'\\n'";
				case '\r': return "'\\r'";
				case '\a': return "'\\a'";
				case '\b': return "'\\b'";
				case '\t': return "'\\t'";
				default: return "'" + std::string(1, ch) + "'";
			}
		}
		if (ampersand)
			return "&" + std::get<const std::string *>(imm)->substr(1);
		return *std::get<const std::string *>(imm);
	}

	std::string toString(const Immediate &imm, const Variable &var, bool ampersand) {
		std::string out = toString(imm, ampersand);
		if (var.type == nullptr) {
			out += "{v}";
		} else {
			out += '{';
			out += var.type->whyString();
			out += '}';
		}
		return out;
	}

	std::string toString(const Immediate &imm, const Variable &var, int pointer_diff) {
		std::string out = toString(imm, false);
		if (var.type == nullptr) {
			out += "{v}";
		} else {
			out += '{';
			out += unwrap(var.type, pointer_diff)->whyString();
			out += '}';
		}
		return out;
	}
}
