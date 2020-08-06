#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>

#include "allocator/ColoringAllocator.h"
#include "compiler/Program.h"
#include "util/Util.h"
#include "Interactive.h"

#define PROMPT "\e[2m>>\e[22m ";

#define GET_FN_SEL() Function *function; if (rest.empty()) { if (!selected) { error() << "No function is selected.\n"; \
	std::cout << PROMPT; continue; } function = selected; } else { if (!checkRest()) { std::cout << \
	PROMPT; continue; } if (program.functions.count(rest) == 0) { error() << "Function \e[1m" << rest << \
	"\e[22m not found.\n"; std::cout << PROMPT; continue; } function = program.functions.at(rest); }

#define GET_FN() if (!selected) { error() << "No function is selected.\n"; std::cout << PROMPT; continue; } Function \
	*function = selected;

namespace LL2W {
	void interactive(Program &program) {
		std::string line;
		std::cout << PROMPT;
		Function *selected = nullptr;

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
					{"info <function|global>", "Shows information about a function or global."},
					{"select <function>     ", "Selects a function."},
					{"compile               ", "Compiles the selected function."},
					{"init                  ", "Performs initial compilation on the selected function."},
					{"attempt               ", "Attempts register allocation on the selected function."},
					{"final                 ", "Performs final compilation on the selected function."},
					{"reset                 ", "Resets the selected function's compilation status flags."},
					{"debug                 ", "Prints the selected function's compiled code in its current state. "
					                           "Options: -blocks, linear, vars, blive, vlive, rw, render, estimations"},
					{"status                ", "Prints the selected function's status flags."},
					{"tried                 ", "Prints the selected function's tried IDs/labels."},
					{"stack                 ", "Prints the selected function's stack allocations."},
					{"spill <variable>      ", "Spills a variable in the selected function."},
					{"pig                   ", "Renders the selected function's interference graph."},
				}) {
					std::cout << "    \e[2m-\e[22m \e[1m" << first << "\e[22m " << second << "\n";
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
				if (rest.empty() && selected) {
					info() << "Function \e[1m" << rest << "\e[22m: " << selected->headerString() << "\n";
					std::cout << PROMPT;
					continue;
				}
				if (!checkRest()) {
					std::cout << PROMPT;
					continue;
				}
				if (program.functions.count(rest) != 0) {
					Function &function = *program.functions.at(rest);
					info() << "Function \e[1m" << rest << "\e[22m: " << function.headerString() << "\n";
				} else if (program.globals.count(rest) != 0) {
					GlobalVarDef *global = program.globals.at(rest);
					info() << "Global \e[1m" << rest << "\e[22m: " << global->debugExtra() << "\n";
				} else error() << "Nothing found for \e[1m" << rest << "\e[22m.\n";
			} else if (Util::isAny(first, {"in", "init", "initial"})) {
				GET_FN();
				if (function->initialDone) {
					warn() << "Initial compilation already done for function \e[1m" << *function->name << ". Use \e[1m"
					       << "reset " << *function->name << "\e[22m to reset the initialDone flag first.\n";
				} else {
					info() << "Running initial compilation for \e[1m" << *function->name << "\e[22m...\n";
					function->initialCompile();
					info() << "Initial compilation for \e[1m" << *function->name << "\e[22m complete.\n";
				}
			} else if (Util::isAny(first, {"a", "attempt"})) {
				GET_FN();
				if (!function->initialDone) {
					warn() << "Initial compilation hasn't been performed for \e[1m" << *function->name << "\e[22m. Use "
					       << "\e[1minit " << *function->name << "\e[22m to perform the initial compilation.\n";
				} else {
					info() << "Running allocation on \e[1m" << *function->name << "\e[22m...\n";
					std::list<std::tuple<Allocator::Result, VariablePtr, VariablePtr>> results;
					const size_t times = Util::isNumeric(rest)? Util::parseLong(rest) : 1;
					for (size_t i = 0; i < times; ++i) {
						Allocator::Result result = function->attemptAllocation();
						results.push_back({result, function->allocator->lastSpill,
							function->allocator->lastSpillAttempt});
					}
					for (const auto &[result, last_spill, last_spill_attempt]: results) {
						if (result == Allocator::Result::Spilled)
							info() << "Allocation result: spilled " << *last_spill << ".\n";
						else if (result == Allocator::Result::NotSpilled)
							info() << "Allocation result: didn't spill " << *last_spill_attempt << ".\n";
						else info() << "Allocation result: " << Allocator::stringify(result) << ".\n";
					}
				}
			} else if (Util::isAny(first, {"f", "final"})) {
				GET_FN();
				if (function->finalDone) {
					warn() << "Final compilation already done for function \e[1m" << *function->name << ". Use \e[1m"
					       << "reset " << *function->name << "\e[22m to reset the finalDone flag first.\n";
				} else {
					info() << "Running final compilation for \e[1m" << *function->name << "\e[22m...\n";
					function->finalCompile();
					info() << "Final compilation for \e[1m" << *function->name << "\e[22m complete.\n";
				}
			} else if (Util::isAny(first, {"r", "reset"})) {
				// Resets the initialDone, allocationDone and finalDone booleans for a function.
				GET_FN();
				function->initialDone = false;
				function->allocationDone = false;
				function->finalDone = false;
			} else if (Util::isAny(first, {"d", "dbg", "debug"})) {
				GET_FN();
				const bool doBlocks      = !Util::contains(split, "-blocks");
				const bool linear        =  Util::contains(split, "linear");
				const bool vars          =  Util::contains(split, "vars");
				const bool blockLiveness =  Util::contains(split, "blive");
				const bool readWritten   =  Util::contains(split, "rw");
				const bool varLiveness   =  Util::contains(split, "vlive");
				const bool render        =  Util::contains(split, "render");
				const bool estimations   =  Util::contains(split, "estimations") || Util::contains(split, "est");
				function->debug(doBlocks, linear, vars, blockLiveness, readWritten, varLiveness, render, estimations);
			} else if (Util::isAny(first, {"st", "status"})) {
				GET_FN();
				info() << "Initial:    " << (function->initialDone? "done" : "not done") << "\n";
				info() << "Allocation: " << (function->allocationDone? "done" : "not done") << "\n";
				info() << "Final:      " << (function->finalDone? "done" : "not done") << "\n";
			} else if (Util::isAny(first, {"s", "sel", "select"})) {
				if (!checkRest()) {
					std::cout << PROMPT;
					continue;
				}
				if (program.functions.count(rest) == 0)
					error() << "Function \e[1m" << rest << "\e[22m not found.\n";
				else
					selected = program.functions.at(rest);
			} else if (Util::isAny(first, {"t", "tr", "tried"})) {
				GET_FN();
				info() << "Tried IDs:   ";
				const std::unordered_set<int> &ids = function->allocator->getTriedIDs();
				for (int tried: std::set<int>(ids.begin(), ids.end()))
					std::cout << " " << tried;
				std::cout << "\n";
				info() << "Tried labels:";
				for (const std::string &tried: Util::nsort(function->allocator->getTriedLabels()))
					std::cout << " " << tried;
				std::cout << "\n";
			} else if (Util::isAny(first, {"stk", "stack"})) {
				GET_FN();
				if (function->stack.empty()) {
					warn() << "No stack locations for \e[1m" << *function->name << "\e[22m.\n";
				} else {
					info() << "Stack locations for \e[1m" << *function->name << "\e[22m:\n";
					for (const std::pair<const int, StackLocation> &pair: function->stack) {
						std::cout << "    \e[2m-\e[22m";
						printStackLocation(pair.second);
					}
				}
			} else if (Util::isAny(first, {"sp", "spill"})) {
				GET_FN();
				if (rest.empty()) {
					error() << "Please specify a variable to spill.\n";
				} else {
					if (rest.front() == '%')
						rest.erase(0, 1);
					if (!Util::isNumeric(rest)) {
						error() << "Expected a numeric variable name.\n";
					} else {
						int id = Util::parseLong(rest);
						if (function->variableStore.count(id) == 0) {
							error() << "Variable not found: \e[1m%" << id << "\e[22m." << (function->initialDone? "\n" :
								" Did you remember to run \e[1minit\e[22m?\n");
						} else {
							VariablePtr variable = function->variableStore.at(id);
							function->addToStack(variable, StackLocation::Purpose::Spill);
							const bool result = function->spill(variable);
							info() << "Spill result: " << (result? "" : "no ") << "instructions were inserted.\n";
							if (result) {
								info() << "Stack location: ";
								printStackLocation(function->getSpill(variable));
							}
						}
					}
				}
			} else if (Util::isAny(first, {"pig", "interference", "🐖", "🐗", "🐷", "🐽"})) {
				GET_FN();
				if (function->allocator->interference.empty()) {
					warn() << "The interference graph is empty. Try \e[1mattempt\e[22m.\n";
				} else {
					function->allocator->interference.renderTo("interference_" + Util::escape(*function->name)
						+ "_x" + std::to_string(function->allocator->getAttempts()) + ".png");
					info() << "Rendering the interference graph in the background.\n";
				}
			} else error() << "Unknown command: \"" << line << "\"\n";
			std::cout << PROMPT;
		}
	}

	void printStackLocation(const StackLocation &location) {
		std::cout << "\e[1m" << std::right << std::setw(4) << location.offset << "\e[22m: "
		          << (location.purpose == StackLocation::Purpose::Alloca? "alloca" : "spill ") << " (width="
		          << location.width << ", align=" << location.align << ") for " << *location.variable << "\n";
	}
}
