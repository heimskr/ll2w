#include <iostream>
#include <climits>
#include <sstream>

#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "options.h"

namespace LL2W {
	Variable::Variable(const std::string *id_, TypePtr type_, const WeakSet<BasicBlock> &defining_blocks,
	const WeakSet<BasicBlock> &using_blocks):
		id(id_), type(type_), definingBlocks(defining_blocks), usingBlocks(using_blocks) {}

	int Variable::weight() const {
		int sum = 0;
		for (std::weak_ptr<BasicBlock> use: usingBlocks)
			sum += use.lock()->estimatedExecutions;
		return sum;
	}

	int Variable::spillCost() {
		if (spillCost_.has_value())
			return spillCost_.value();

		// If a variable is never used, it has a negative spill cost.
		if (uses.empty())
			return *(spillCost_ = -1);

		// If a variable has only one use and that use is right after its one definition, it has an (effectively)
		// infinite spill cost.
		if (definitions.size() == 1 && uses.size() == 1) {
			if (uses.begin()->lock()->index == definitions.begin()->lock()->index + 1)
				return *(spillCost_ = INT_MAX);
		}

		return *(spillCost_ = weight());
	}

	void Variable::clearSpillCost() {
		spillCost_.reset();
	}

	bool Variable::isSimple() const {
		return definingBlocks.size() == 1 && usingBlocks.size() == 1
			&& (*usingBlocks.begin()).lock()->index == (*definingBlocks.begin()).lock()->index;
	}

	bool Variable::operator==(const Variable &other) const {
		return id == other.id && (type == other.type || *type == *other.type);
	}

	Variable::operator std::string() const {
		std::stringstream out;
		const std::string base;
		if (reg == -1)
			out << "\e[32m%" << *id << "\e[39m";
		else
			out << "\e[92m$" << WhyInfo::registerName(reg) << "\e[39;2m:\e[32m" << *id << "\e[39;22m";
#ifdef VARIABLE_EXTRA
		std::unordered_set<Variable *> alias_set = parent? parent->aliases : aliases;
		if (!alias_set.empty()) {
			out << "\e[2m[";
			for (auto begin = alias_set.begin(), iter = begin, end = alias_set.end(); iter != end; ++iter) {
				if (iter != begin)
					out << ",";
				out << *(*iter)->id << "x" << (*iter)->definitions.size() << "." << (*iter)->definingBlocks.size();
			}
			out << "]\e[22m";
		}
		out << "\e[2m<" << definingBlocks.size() << "." << definitions.size() << ":" << usingBlocks.size() << "."
		    << uses.size() << ">\e[22m";
#endif
		return out.str();
	}

	std::string Variable::toString() const {
		return reg != -1? "$" + WhyInfo::registerName(reg) : *this;
	}

	std::string Variable::plainString() const {
		if (reg == -1)
			return "%" + *id;
		return "$" + WhyInfo::registerName(reg) + ":" + *id;
	}

	void Variable::makeAliasOf(Variable &new_parent) {
		if (&new_parent == this || new_parent.aliases.count(this) != 0)
			return;

		std::cerr << *this << ".makeAliasOf(" << new_parent << ")\n";

		parent = &new_parent;
		new_parent.aliases.insert(this);
		for (Variable *alias: aliases) {
			alias->parent = &new_parent;
			new_parent.aliases.insert(alias);
		}
		for (const std::weak_ptr<BasicBlock> &def: definingBlocks)
			new_parent.definingBlocks.insert(def);
		for (const std::weak_ptr<BasicBlock> &use: usingBlocks)
			new_parent.usingBlocks.insert(use);
		for (const std::weak_ptr<Instruction> &def: definitions)
			new_parent.definitions.insert(def.lock());
		for (const std::weak_ptr<Instruction> &use: uses)
			new_parent.uses.insert(use.lock());
		id = new_parent.id;
		type = new_parent.type;
		lastUse = new_parent.lastUse;
		definingBlocks = new_parent.definingBlocks;
		usingBlocks = new_parent.usingBlocks;
		definitions = new_parent.definitions;
		uses = new_parent.uses;
	}

	void Variable::addDefiner(std::shared_ptr<BasicBlock> block) {
		if (parent) {
			parent->addDefiner(block);
		} else {
			definingBlocks.insert(block);
			for (Variable *alias: aliases)
				alias->definingBlocks.insert(block);
		}
	}

	void Variable::removeDefiner(std::shared_ptr<BasicBlock> block) {
		if (parent) {
			parent->removeDefiner(block);
		} else {
			definingBlocks.erase(block);
			for (Variable *alias: aliases)
				alias->definingBlocks.erase(block);
		}
	}

	void Variable::addUsingBlock(std::shared_ptr<BasicBlock> block) {
		if (parent) {
			parent->addUsingBlock(block);
		} else {
			usingBlocks.insert(block);
			for (Variable *alias: aliases)
				alias->usingBlocks.insert(block);
		}
	}

	void Variable::removeUsingBlock(std::shared_ptr<BasicBlock> block) {
		if (parent) {
			parent->removeUsingBlock(block);
		} else {
			usingBlocks.erase(block);
			for (Variable *alias: aliases)
				alias->usingBlocks.erase(block);
		}
	}

	void Variable::addDefinition(std::shared_ptr<Instruction> instruction) {
		if (parent) {
			parent->addDefinition(instruction);
		} else {
			definitions.insert(instruction);
			for (Variable *alias: aliases)
				alias->definitions.insert(instruction);
		}
	}

	void Variable::removeDefinition(std::shared_ptr<Instruction> instruction) {
		if (parent) {
			parent->removeDefinition(instruction);
		} else {
			definitions.erase(instruction);
			for (Variable *alias: aliases)
				alias->definitions.erase(instruction);
		}
	}

	void Variable::addUse(std::shared_ptr<Instruction> instruction) {
		if (parent) {
			parent->addUse(instruction);
		} else {
			uses.insert(instruction);
			for (Variable *alias: aliases)
				alias->uses.insert(instruction);
		}
	}

	void Variable::removeUse(std::shared_ptr<Instruction> instruction) {
		if (parent) {
			parent->removeUse(instruction);
		} else {
			uses.erase(instruction);
			for (Variable *alias: aliases)
				alias->uses.erase(instruction);
		}
	}

	std::shared_ptr<BasicBlock> Variable::onlyDefiner() const {
		if (definingBlocks.size() != 1) {
			throw std::runtime_error("Variable has " + std::string(definingBlocks.empty()? "no" : "multiple") +
				" defining blocks");
		}

		return definingBlocks.begin()->lock();
	}

	std::shared_ptr<Instruction> Variable::onlyDefinition() const {
		if (definitions.size() != 1) {
			std::cerr << "[Bad variable: " << *this << "]\n";
			for (auto weak: definitions)
				std::cerr << "\e[31;2m-\e[0m " << weak.lock()->debugExtra() << "\n";
			throw std::runtime_error("Variable has " + std::string(definitions.empty()? "no" : "multiple") +
				" definitions");
		}

		return definitions.begin()->lock();
	}

	void Variable::setType(TypePtr new_type) {
		if (parent) {
			parent->setType(new_type);
		} else {
			type = new_type? new_type->copy() : nullptr;
			for (Variable *alias: aliases)
				alias->type = type;
		}
	}

#define VARSETTER(method, type, param, field) \
	void Variable::set##method(type param) { \
		if (parent) { \
			parent->set##method(param); \
		} else { \
			field = param; \
			for (Variable *alias: aliases) \
				alias->field = param; \
		} \
	}

	VARSETTER(ID, const std::string *, new_id, id)
	VARSETTER(DefiningBlocks, const decltype(Variable::definingBlocks) &, block, definingBlocks)
	VARSETTER(Definitions, const decltype(Variable::definitions) &, defs, definitions)
	VARSETTER(Uses, const decltype(Variable::uses) &, new_uses, uses)
	VARSETTER(UsingBlocks, const decltype(Variable::usingBlocks) &, blocks, usingBlocks)
	VARSETTER(LastUse, decltype(Variable::lastUse), use, lastUse);
	VARSETTER(Register, int, new_reg, reg);

	std::ostream & operator<<(std::ostream &os, const LL2W::Variable &var) {
		return os << std::string(var);
	}

	void Variable::debug() {
		std::cerr << *this << "\n";
		std::cerr << "   Defining blocks:";
		for (const std::weak_ptr<BasicBlock> &block: definingBlocks)
			std::cerr << " %" << block.lock()->label;
		std::cerr << "\n";
		std::cerr << "   Using blocks:";
		for (const std::weak_ptr<BasicBlock> &block: usingBlocks)
			std::cerr << " %" << block.lock()->label;
		std::cerr << "\n";
		std::cerr << "   Last use: ";
		if (InstructionPtr last_use = lastUse.lock())
			std::cerr << lastUse.lock()->debugExtra() << "\n";
		else
			std::cerr << "\e[2mnone\e[22m\n";
		if (definitions.empty()) {
			std::cerr << "   No definitions.\n";
		} else {
			std::cerr << "   Definitions (" << definitions.size() << "):\n";
			for (const std::weak_ptr<Instruction> &instruction: definitions)
				std::cerr << "      " << instruction.lock()->debugExtra() << "\n";
		}
		if (aliases.empty()) {
			std::cerr << "   No aliases.\n";
		} else {
			std::cerr << "   Aliases:";
			for (const Variable *alias: aliases)
				std::cerr << " " << *alias;
			std::cerr << "\n";
		}
	}
}
