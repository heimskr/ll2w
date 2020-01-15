#include <iostream>

#include "ASTNode.h"
#include "StringSet.h"
#include "Parser.h"
#include "Lexer.h"

namespace LL2W {
	Location::operator std::string() const {
		return *filename() + ":" + std::to_string(line + 1) + "." + std::to_string(column);
	}

	const std::string * Location::filename() const {
		static std::string wh = "?"; return &wh;
		// return "?";
	}

	std::ostream & operator<<(std::ostream &os, const Location &location) {
		os << std::string(location);
		return os;
	}

	ASTNode::ASTNode(int sym, const Location &loc, const char *info) {
		symbol = sym;
		location = loc;
		lexerInfo = StringSet::intern(info);
	}

	ASTNode::ASTNode(int sym, const Location &loc, const std::string *info):
		symbol(sym), location(loc), lexerInfo(info) {}

	ASTNode::ASTNode(int sym, const std::string *info): symbol(sym), location(Lexer::location), lexerInfo(info) {}

	ASTNode::ASTNode(int sym, const char *info) {
		symbol = sym;
		location = Lexer::location;
		lexerInfo = StringSet::intern(info);
	}

	ASTNode::~ASTNode() {
		for (ASTNode *child: children)
			delete child;
	}

	ASTNode * ASTNode::adopt(ASTNode *child) {
		if (child) {
			children.push_back(child);
			child->parent = this;
		}

		return this;
	}

	ASTNode * ASTNode::adopt(std::initializer_list<ASTNode *> to_add) {
		for (ASTNode *child: to_add)
			adopt(child);
		return this;
	}

	ASTNode * ASTNode::absorb(ASTNode *to_absorb) {
		for (ASTNode *child: to_absorb->children)
			adopt(child);
		to_absorb->children.clear();
		delete to_absorb;
		return this;
	}

	ASTNode * ASTNode::clear() {
		for (ASTNode *child: children)
			delete child;
		children.clear();
		return this;
	}

	std::string ASTNode::concatenate() const {
		std::string out;
		for (ASTNode *child: children)
			out += *child->lexerInfo;
		return out;
	}

	void ASTNode::debug(int indent) {
		for (int i = 0; i < indent; ++i)
			std::cerr << "\e[2m│\e[0m   ";
		std::cerr << "\e[1m" << Parser::getName(symbol) << "\e[0;2m @" << location << "\x1b[0;35m " << *lexerInfo;
		std::cerr << "\e[0m" << debugExtra() << "\n";
		for (ASTNode *child: children)
			child->debug(indent + 1);
	}

	std::string ASTNode::debugExtra() {
		return "";
	}

	void ASTNode::destroy(std::initializer_list<ASTNode *> to_destroy) {
		for (ASTNode *node: to_destroy) {
			if (node)
				delete node;
		}
	}

	MetadataDef::MetadataDef(ASTNode *dotident_node, ASTNode *distinct_node, ASTNode *list):
		ASTNode(TOK_METADATA, StringSet::intern(dotident_node->concatenate().c_str())) {
		distinct = distinct_node != nullptr;
		if (distinct_node)
			delete distinct_node;
		adopt(dotident_node);
		adopt(list);
	}

	std::string MetadataDef::debugExtra() {
		return " \e[36m" + std::string(distinct? "" : "not ") + "distinct";
	}
}
