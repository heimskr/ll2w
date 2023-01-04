#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>

#include <limits.h>

#include "allocator/ColoringAllocator.h"
#include "compiler/Program.h"
#include "util/Util.h"
#include "Interactive.h"

#define PROMPT "\e[2m>>\e[22m ";
#define DASH "\e[2m-\e[22m"

#define GET_FN_SEL() Function *function; if (rest.empty()) { if (!selected) { error() << "No function is selected.\n"; \
	std::cerr << PROMPT; continue; } function = selected; } else { if (!checkRest()) { std::cerr << \
	PROMPT; continue; } if (program.functions.count(rest) == 0) { error() << "Function \e[1m" << rest << \
	"\e[22m not found.\n"; std::cerr << PROMPT; continue; } function = program.functions.at(rest); }

#define GET_FN() if (!selected) { error() << "No function is selected.\n"; std::cerr << PROMPT; continue; } Function \
	*function = selected;

namespace LL2W {
	void interactive(Program &program, Function *selected) {
		std::string line;
		std::cerr << PROMPT;

		while (std::getline(std::cin, line)) {
			const size_t space = line.find(' ');
			const std::string first = line.substr(0, space);
			std::string rest = space == std::string::npos? "" : line.substr(space + 1);
			const std::vector<std::string> split = Util::split(rest, " ", false);
			std::string lastRest;

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
					{"attempt               ", "Attempts register allocation on the selected function."},
					{"compile               ", "Compiles the selected function."},
					{"debug                 ", "Prints the selected function's compiled code in its current state. "
					                           "Options: -blocks, linear, vars, blive, vlive, rw, render, estimations"
											   ", aliases, stack"},
					{"edges <id>            ", "Prints the edges for a given node in the selected function's "
					                           "interference graph."},
					{"final                 ", "Performs final compilation on the selected function."},
					{"hd <limit>            ", "Prints the interference graph nodes in descending order of degree."},
					{"init                  ", "Performs initial compilation on the selected function."},
					{"mig                   ", "Makes an interference graph for the selected function."},
					{"pig                   ", "Renders the selected function's interference graph."},
					{"pcfg                  ", "Renders the selected function's control flow graph."},
					{"reset                 ", "Resets the selected function's compilation status flags."},
					{"spill <variable>      ", "Spills a variable in the selected function."},
					{"stack                 ", "Prints the selected function's stack allocations."},
					{"status                ", "Prints the selected function's status flags."},
					{"tried                 ", "Prints the selected function's tried IDs/labels."},
					{"var <id>              ", "Prints information about a variable in the selected function."},
				}) {
					std::cerr << "    " DASH " \e[1m" << first << "\e[22m " << second << "\n";
				}
			} else if (Util::isAny(first, {"l", "ls", "list"})) {
				if (Util::isAny(rest, {"", "f", "fn", "func", "function"})) {
					for (const std::pair<const std::string, LL2W::Function *> &pair: Util::mapnsort(program.functions))
						std::cerr << DASH " " << pair.second->headerString() << "\n";
				} else if (Util::isAny(rest, {"g", "gl", "global", "globals"})) {
					for (const std::pair<const std::string, GlobalVarDef *> &pair: Util::mapnsort(program.globals))
						std::cerr << DASH " " << pair.first << "\n";
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
					std::cerr << PROMPT;
					continue;
				}
				if (!checkRest()) {
					std::cerr << PROMPT;
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
				const bool aliases       =  Util::contains(split, "aliases") || Util::contains(split, "al");
				const bool stack         =  Util::contains(split, "stack") || Util::contains(split, "st");
				const bool labels        =  Util::contains(split, "labels") || Util::contains(split, "lb");
				function->debug(doBlocks, linear, vars, blockLiveness, readWritten, varLiveness, render, estimations,
					aliases, stack, labels);
			} else if (Util::isAny(first, {"st", "status"})) {
				GET_FN();
				info() << "Initial:    " << (function->initialDone? "done" : "not done") << "\n";
				info() << "Allocation: " << (function->allocationDone? "done" : "not done") << "\n";
				info() << "Final:      " << (function->finalDone? "done" : "not done") << "\n";
			} else if (Util::isAny(first, {"s", "sel", "select"})) {
				if (!checkRest()) {
					std::cerr << PROMPT;
					continue;
				}
				if (program.functions.count(rest) == 0)
					error() << "Function \e[1m" << rest << "\e[22m not found.\n";
				else
					selected = program.functions.at(rest);
			} else if (Util::isAny(first, {"t", "tr", "tried"})) {
				GET_FN();
				info() << "Tried IDs:   ";
				const auto &ids = function->allocator->getTriedIDs();
				for (const Variable::ID tried: std::set<Variable::ID>(ids.begin(), ids.end()))
					std::cerr << " " << *tried;
				std::cerr << "\n";
				info() << "Tried labels:";
				for (const std::string &tried: Util::nsort(function->allocator->getTriedLabels()))
					std::cerr << " " << tried;
				std::cerr << "\n";
			} else if (Util::isAny(first, {"stk", "stack"})) {
				GET_FN();
				if (function->stack.empty()) {
					warn() << "No stack locations for \e[1m" << *function->name << "\e[22m.\n";
				} else {
					info() << "Stack locations for \e[1m" << *function->name << "\e[22m:\n";
					for (const std::pair<const int, StackLocation> &pair: function->stack) {
						std::cerr << "    " DASH;
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
					const std::string *id = StringSet::intern(rest);
					if (function->variableStore.count(id) == 0) {
						error() << "Variable not found: \e[1m%" << *id << "\e[22m." << (function->initialDone? "\n" :
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
			} else if (Util::isAny(first, {"pig", "interference", "🐖", "🐗", "🐷", "🐽"})) {
				GET_FN();
				if (function->allocator->interference.empty()) {
					warn() << "The interference graph is empty. Try \e[1mattempt\e[22m.\n";
				} else {
					function->allocator->interference.renderTo("interference_" + Util::escape(*function->name)
						+ "_x" + std::to_string(function->allocator->getAttempts()) + ".pdf");
					info() << "Rendering the interference graph in the background.\n";
				}
			} else if (Util::isAny(first, {"pcfg"})) {
				GET_FN();
				if (function->cfg.empty()) {
					warn() << "The control flow graph is empty. Try \e[1minit\e[22m.\n";
				} else {
					function->cfg.renderTo("./cfg_" + Util::escape(*function->name) + ".pdf");
					info() << "Rendering the CFG in the background.\n";
				}
			} else if (Util::isAny(first, {"hd", "highest"})) {
				GET_FN();
				if (function->allocator->interference.empty()) {
					warn() << "The interference graph is empty. Try \e[1mattempt\e[22m.\n";
				} else {
					size_t max = SIZE_MAX;
					if (!rest.empty()) {
						if (!Util::isNumeric(rest)) {
							error() << "Invalid limit specified.\n";
							std::cerr << PROMPT;
							continue;
						}
						max = Util::parseLong(rest);
					}

					std::vector<std::pair<int, Node *>> nodes;
					for (Node *node: function->allocator->interference.nodes())
						nodes.push_back({node->degree(), node});
					std::sort(nodes.begin(), nodes.end(), [](const auto &left, const auto &right) {
						return left.first > right.first;
					});
					if (nodes.size() < max)
						max = nodes.size();
					for (size_t i = 0; i < max; ++i)
						std::cerr << DASH " %" << nodes[i].second->label() << ": " << nodes[i].first << "\n";
				}
			} else if (Util::isAny(first, {"m", "make", "mig"})) {
				GET_FN();
				function->allocator->makeInterferenceGraph();
				info() << "Generated an interference graph for \e[1m" << *function->name << "\e[22m.\n";
			} else if (Util::isAny(first, {"e", "ed", "edges"})) {
				GET_FN();
				if (function->allocator->interference.empty()) {
					warn() << "The interference graph is empty. Try \e[1mattempt\e[22m.\n";
				} else if (rest.empty()) {
					error() << "Please specify a node label.\n";
				} else {
					if (rest.front() == '%')
						rest.erase(0, 1);
					Graph &interference = function->allocator->interference;
					if (!interference.hasLabel(rest)) {
						error() << "Couldn't find \e[1m%" << rest << "\e[22m.\n";
					} else {
						bool first = true;
						for (Node *neighbor: interference[rest].allEdges()) {
							if (!first)
								std::cerr << " ";
							else
								first = false;
							std::cerr << neighbor->label();
						}
						std::cerr << "\n";
					}
				}
			} else if (Util::isAny(first, {"v", "var", "variable"})) {
				GET_FN();
				if (!rest.empty() && rest.front() == '%')
					rest.erase(0, 1);
				Variable::ID id = StringSet::intern(rest);
				if (function->variableStore.count(id) == 0) {
					error() << "Variable \e[1m%" << *id << "\e[22m not found.\n";
				} else {
					VariablePtr variable = function->variableStore.at(id);
					auto sparent = variable->getParent().lock();
					if (sparent)
						info() << "Parent: " << *sparent << "\n";
					if (!variable->getAliases().empty()) {
						std::ostream &stream = info() << "Aliases:";
						for (Variable *alias: variable->getAliases())
							stream << " " << *alias << " \e[2m" << alias->originalID << "\e[22m";
						stream << "\n";
					} else if (sparent && !sparent->getAliases().empty()) {
						// TODO: reduce code duplication
						std::ostream &stream = info() << "Aliases:";
						for (Variable *alias: sparent->getAliases())
							stream << " " << *alias << " \e[2m" << alias->originalID << "\e[22m";
						stream << "\n";
					}
					info() << "Defining blocks:\n";
					for (const std::weak_ptr<BasicBlock> &def: variable->definingBlocks)
						std::cerr << DASH " %" << *def.lock()->label << "\n";
					info() << "Using blocks:\n";
					for (const std::weak_ptr<BasicBlock> &use: variable->usingBlocks)
						std::cerr << DASH " %" << *use.lock()->label << "\n";
					const int spill_cost = variable->spillCost();
					info() << "Spill cost: \e[1m" << (spill_cost == INT_MAX? "∞" : std::to_string(spill_cost))
							<< "\e[22m\n";
					bool live_in_anywhere = false, live_out_anywhere = false;
					const std::vector<BasicBlockPtr> sorted_blocks = Util::nsort(function->blocks,
						[](const BasicBlockPtr &block) -> const std::string & {
							return *block->label;
						}, true);
					for (const BasicBlockPtr &block: sorted_blocks)
						if (block->isLiveIn(variable)) {
							live_in_anywhere = true;
							break;
						}
					for (const BasicBlockPtr &block: sorted_blocks)
						if (block->isLiveOut(variable)) {
							live_out_anywhere = true;
							break;
						}
					if (live_in_anywhere) {
						info() << "Live-in at:\n";
						for (const BasicBlockPtr &block: sorted_blocks)
							if (block->isLiveIn(variable))
								std::cerr << DASH " %" << *block->label << "\n";
					}
					if (live_out_anywhere) {
						info() << "Live-out at:\n";
						for (const BasicBlockPtr &block: sorted_blocks)
							if (block->isLiveOut(variable))
								std::cerr << DASH " %" << *block->label << "\n";
					}
				}
			} else if (Util::isAny(first, {"rl", "resetlive"})) {
				GET_FN();
				function->resetLiveness();
				for (BasicBlockPtr &block: function->blocks)
					block->extract(true);
				function->extractVariables(true);
				function->computeLiveness();
				info() << "Recomputed liveness data for \e[1m" << *function->name << "\e[22m.\n";
			} else error() << "Unknown command: \"" << line << "\"\n";
			std::cerr << PROMPT;
		}
	}

	void printStackLocation(const StackLocation &location) {
		std::cerr << "\e[1m" << std::right << std::setw(4) << location.offset << "\e[22m: "
		          << (location.purpose == StackLocation::Purpose::Alloca? "alloca" : "spill ") << " (width="
		          << location.width << ", align=" << location.align << ") for " << *location.variable << "\n";
	}
}
