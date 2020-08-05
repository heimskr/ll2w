#include <functional>
#include <iostream>
#include <string>

#include "compiler/Program.h"
#include "util/Util.h"
#include "Interactive.h"

#define GET_FN() if (!checkRest()) continue; if (program.functions.count(rest) == 0) { error() << "Function \e[1m" << \
	rest << "\e[22m not found.\n"; continue; } Function &function = *program.functions.at(rest);

namespace LL2W {
	void interactive(Program &program) {
		std::string line;
		std::cout << "\e[2m>>\e[22m ";
		while (std::getline(std::cin, line)) {
			const size_t space = line.find(' ');
			const std::string first = line.substr(0, space);
			std::string rest = space == std::string::npos? "" : line.substr(space + 1);
			const std::vector<std::string> split = Util::split(rest, " ", false);
			std::string lastRest;
			// const size_t size = split.size();

			std::function<bool()> checkRest = [&]() -> bool {
				if (rest == "_")
					rest = lastRest;
				if (rest.empty()) {
					error() << "Argument expected.\n";
					return false;
				}
				if (rest.front() != '@')
					rest = '@' + rest;
				lastRest = rest;
				return true;
			};

			if (Util::isAny(first, {"h", "?", "help"})) {
				info() << "Available commands:\n";
				for (const auto &[first, second]: std::initializer_list<std::pair<const char *, const char *>> {
					{"ls f                  ", "Lists all functions."},
					{"ls g                  ", "Lists all globals."},
					{"compile <function>    ", "Compiles a function."},
					{"info <function|global>", "Shows information about a function or global."},
					{"init <function>       ", "Performs initial compilation on a function."},
					{"attempt <function>    ", "Attempts register allocation on a function."},
					{"final <function>      ", "Performs final compilation on a function."},
					{"reset <function>      ", "Resets a function's compilation status flags."},
					{"debug <function>      ", "Prints a function's compiled code in its current state."},
					{"status <function>     ", "Prints a function's status flags."},
				}) {
					std::cerr << "    \e[2m-\e[22m \e[1m" << first << "\e[22m " << second << "\n";
				}
			} else if (Util::isAny(first, {"l", "ls", "list"})) {
				if (Util::isAny(rest, {"", "f", "fn", "func", "function"})) {
					for (const std::pair<const std::string, LL2W::Function *> &pair: Util::mapnsort(program.functions))
						std::cout << "\e[2m-\e[22m " << pair.second->headerString() << "\n";
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
						fn = program.functions.at(rest);
					} else if (program.functions.count("@" + rest) != 0) {
						fn = program.functions.at("@" + rest);
					} else {
						error() << "Couldn't find function \e[1m" << rest << "\e[22m.\n";
					}

					if (fn)
						fn->compile();
				}
			} else if (Util::isAny(first, {"i", "info"})) {
				if (!checkRest())
					continue;
				if (program.functions.count(rest) != 0) {
					Function &function = *program.functions.at(rest);
					info() << "Function \e[1m" << rest << "\e[22m: " << function.headerString() << "\n";
				} else if (program.globals.count(rest) != 0) {
					GlobalVarDef *global = program.globals.at(rest);
					info() << "Global \e[1m" << rest << "\e[22m: " << global->debugExtra() << "\n";
				} else error() << "Nothing found for \e[1m" << rest << "\e[22m.\n";
			} else if (Util::isAny(first, {"in", "init", "initial"})) {
				GET_FN();
				if (function.initialDone) {
					warn() << "Initial compilation already done for function \e[1m" << *function.name << ". Use \e[1m"
					       << "reset " << *function.name << "\e[22m to reset the initialDone flag first.\n";
				} else {
					info() << "Running initial compilation for \e[1m" << *function.name << "\e[22m...\n";
					function.initialCompile();
					info() << "Initial compilation for \e[1m" << *function.name << "\e[22m complete.\n";
				}
			} else if (Util::isAny(first, {"a", "attempt"})) {
				GET_FN();
				if (!function.initialDone) {
					warn() << "Initial compilation hasn't been performed for \e[1m" << *function.name << "\e[22m. Use"
					       << "\e[1minit " << *function.name << "\e[22m to perform the initial compilation.\n";
				} else {
					info() << "Running allocation on \e[1m" << *function.name << "\e[22m...\n";
					const Allocator::Result result = function.attemptAllocation();
					if (result == Allocator::Result::Spilled) {
						info() << "Allocation result: spilled " << *function.allocator->lastSpill << ".\n";
					} else if (result == Allocator::Result::NotSpilled) {
						info() << "Allocation result: didn't spill " << *function.allocator->lastSpillAttempt << ".\n";
					} else info() << "Allocation result: " << Allocator::stringify(result) << ".\n";
				}
			} else if (Util::isAny(first, {"f", "final"})) {
				GET_FN();
				if (function.finalDone) {
					warn() << "Final compilation already done for function \e[1m" << *function.name << ". Use \e[1m"
					       << "reset " << *function.name << "\e[22m to reset the finalDone flag first.\n";
				} else {
					info() << "Running final compilation for \e[1m" << *function.name << "\e[22m...\n";
					function.finalCompile();
					info() << "Final compilation for \e[1m" << *function.name << "\e[22m complete.\n";
				}
			} else if (Util::isAny(first, {"r", "reset"})) {
				// Resets the initialDone, allocationDone and finalDone booleans for a function.
				GET_FN();
				function.initialDone = false;
				function.allocationDone = false;
				function.finalDone = false;
			} else if (Util::isAny(first, {"d", "dbg", "debug"})) {
				GET_FN();
				function.debug();
			} else if (Util::isAny(first, {"s", "st", "status"})) {
				GET_FN();
				info() << "Initial:    " << (function.initialDone? "done" : "not done") << "\n";
				info() << "Allocation: " << (function.allocationDone? "done" : "not done") << "\n";
				info() << "Final:      " << (function.finalDone? "done" : "not done") << "\n";
			} else error() << "Unknown command: \"" << line << "\"\n";
			std::cout << "\e[2m>>\e[22m ";
		}
	}
}
