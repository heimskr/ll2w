#include <climits>

#include "compiler/BasicBlock.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"

namespace LL2W {
	Variable::Variable(int id_, Type *type_, const std::set<std::shared_ptr<BasicBlock>> &defining_blocks,
	const std::set<BasicBlockPtr> &using_blocks):
		id(id_), type(type_), definingBlocks(defining_blocks), usingBlocks(using_blocks) {}

	Variable::~Variable() {
		if (type && !parent)
			delete type;
	}

	int Variable::weight() const {
		int sum = 0;
		for (BasicBlockPtr use: usingBlocks)
			sum += use->estimatedExecutions;
		return sum;
	}

	int Variable::spillCost() const {
		// If a variable is never used, it has a negative spill cost.
		if (uses.empty())
			return -1;
		// If a variable has only one use and that use is right after its one definition, it has an (effectively)
		// infinite spill cost.
		if (definitions.size() == 1 && uses.size() == 1 && (*uses.begin())->index == (*definitions.begin())->index + 1)
			return INT_MAX;
		return weight();
	}

	bool Variable::operator==(const Variable &other) const {
		return id == other.id && *type == *other.type;
	}

	Variable::operator std::string() const {
		return reg == -1? "%" + std::to_string(id) : "$" + WhyInfo::registerName(reg);
	}

	void Variable::makeAliasOf(Variable &new_parent) {
		if (type && !parent)
			delete type;
		parent = &new_parent;
		new_parent.aliases.insert(this);
		for (Variable *alias: aliases) {
			alias->parent = &new_parent;
			new_parent.aliases.insert(alias);
		}
		for (const std::shared_ptr<BasicBlock> &def: definingBlocks)
			new_parent.definingBlocks.insert(def);
		for (const std::shared_ptr<BasicBlock> &use: usingBlocks)
			new_parent.usingBlocks.insert(use);
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

	std::shared_ptr<BasicBlock> Variable::onlyDefinition() const {
		if (definingBlocks.size() != 1) {
			throw std::runtime_error("Variable has " + std::string(definingBlocks.empty()? "no" : "multiple") +
				" defining blocks");
		}

		return *definingBlocks.begin();
	}

	void Variable::setType(Type *new_type) {
		if (parent) {
			parent->setType(new_type);
		} else {
			if (type)
				delete type;
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

	VARSETTER(ID, int, new_id, id)
	VARSETTER(DefiningBlocks, const std::set<std::shared_ptr<BasicBlock>> &, block, definingBlocks)
	VARSETTER(Definitions, const std::set<Instruction *> &, defs, definitions)
	VARSETTER(Uses, const std::set<Instruction *> &, new_uses, uses)
	VARSETTER(UsingBlocks, const std::set<std::shared_ptr<BasicBlock>> &, blocks, usingBlocks)
	VARSETTER(LastUse, Instruction *, use, lastUse);
	VARSETTER(Register, int, new_reg, reg);
}
