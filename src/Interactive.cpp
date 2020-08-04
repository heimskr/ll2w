#include <iostream>
#include <string>

#include "compiler/Program.h"
#include "util/Util.h"
#include "Interactive.h"

namespace LL2W {
	void interactive(Program &program) {
		std::string line;
		std::cout << "\e[2m>>\e[22m ";
		while (std::getline(std::cin, line)) {
			const size_t space = line.find(' ');
			const std::string first = line.substr(0, space);
			std::string rest = space == std::string::npos? "" : line.substr(space + 1);
			const std::vector<std::string> split = Util::split(rest, " ", false);
			// const size_t size = split.size();

			if (Util::isAny(first, {"ls", "list", "l"})) {
				if (Util::isAny(rest, {"", "f", "fn", "func", "function"})) {
					for (const std::pair<const std::string, LL2W::Function> &pair: Util::mapnsort(program.functions))
						std::cout << "\e[2m-\e[22m " << pair.second.headerString() << "\n";
				} else if (Util::isAny(rest, {"g", "gl", "global", "globals"})) {
					for (const std::pair<const std::string, GlobalVarDef *> &pair: Util::mapnsort(program.globals))
						std::cout << "\e[2m-\e[22m " << pair.first << "\n";
				} else error() << "ls: Not sure what \"" << rest << "\" is.\n";
			} else if (Util::isAny(first, {"c", "comp", "compile"})) {
				if (rest.empty()) {
					program.compile();
					info() << "Program compiled.\n";
				} else {
					LL2W::Function *fn = nullptr;
					if (program.functions.count(rest) != 0) {
						fn = &program.functions.at(rest);
					} else if (program.functions.count("@" + rest) != 0) {
						fn = &program.functions.at("@" + rest);
					} else {
						error() << "Couldn't find function \e[1m" << rest << "\e[22m.\n";
					}

					if (fn)
						fn->compile();
				}
			} else if (Util::isAny(first, {"i", "info"})) {
				if (rest.empty()) {
					error() << "Argument expected.\n";
					continue;
				}

				if (rest.front() != '@')
					rest = '@' + rest;

				if (program.functions.count(rest) != 0) {
					Function &function = program.functions.at(rest);
					info() << "Function \e[1m" << rest << "\e[22m: " << function.headerString() << "\n";
				} else if (program.globals.count(rest) != 0) {
					GlobalVarDef *global = program.globals.at(rest);
					info() << "Global \e[1m" << rest << "\e[22m: " << global->debugExtra() << "\n";
				} else error() << "Nothing found for \e[1m" << rest << "\e[22m.\n";
			} else error() << "Unknown command: \"" << line << "\"\n";
			std::cout << "\e[2m>>\e[22m ";
		}
	}
}
