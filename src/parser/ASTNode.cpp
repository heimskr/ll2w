#include <iostream>
#include <sstream>

#include "parser/ASTNode.h"
#include "parser/StringSet.h"
#include "parser/Parser.h"
#include "parser/Lexer.h"
#include "parser/Types.h"
#include "util/Util.h"

namespace LL2W {
	Location::operator std::string() const {
		return std::to_string(line + 1) + ":" + std::to_string(column);
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

	ASTNode::ASTNode(int sym, const Location &loc): ASTNode(sym, loc, "") {}

	ASTNode::ASTNode(int sym): ASTNode(sym, "") {}

	ASTNode::ASTNode(int sym, ASTNode *node, const char *info): ASTNode(sym, node->location, info) {
		adopt(node);
	}

	ASTNode::ASTNode(int sym, ASTNode *node, const std::string *info): ASTNode(sym, node->location, info) {
		adopt(node);
	}

	ASTNode::~ASTNode() {
		for (ASTNode *child: children)
			delete child;
	}

	ASTNode * ASTNode::operator[](size_t index) const {
		return at(index);
	}

	ASTNode * ASTNode::at(size_t index) const {
		return *std::next(children.begin(), index);
	}

	size_t ASTNode::size() const {
		return children.size();
	}

	bool ASTNode::empty() const {
		return children.empty();
	}

	ASTNode * ASTNode::adopt(ASTNode *child, bool do_locate) {
		if (child) {
			if (do_locate)
				locate(child);
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
		if (!to_absorb)
			return this;

		for (auto iter = children.begin(), end = children.end(); iter != end; ++iter) {
			if (*iter == to_absorb) {
				children.erase(iter);
				break;
			}
		}

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

	ASTNode * ASTNode::copy() const {
		ASTNode *out = new ASTNode();
		out->symbol = symbol;
		out->location = location;
		out->lexerInfo = lexerInfo;
		out->parent = parent;
		for (ASTNode *child: children) {
			ASTNode *copy = child->copy();
			copy->parent = out;
			out->children.push_back(copy);
		}

		return out;
	}

	ASTNode * ASTNode::locate(const ASTNode *source) {
		if (source)
			location = source->location;
		return this;
	}

	ASTNode * ASTNode::locate(std::initializer_list<const ASTNode *> sources) {
		for (const ASTNode *source: sources) {
			if (source) {
				location = source->location;
				return this;
			}
		}
		return this;
	}

	ASTNode * ASTNode::locate(const Location &loc) {
		location = loc;
		return this;
	}

	std::string ASTNode::concatenate() const {
		if (symbol == VECTOR) {
			std::stringstream out;
			out << "\e[2m<\e[0m";
			auto begin = cbegin();
			for (auto iter = begin, end = cend(); iter != end; ++iter) {
				const ASTNode &comma = **iter;
				if (iter != begin)
					out << "\e[2m,\e[0m ";
				out << comma[0]->concatenate() << " " << comma[1]->concatenate();
			}
			out << "\e[2m>\e[0m";
			return out.str();
		} else if (symbol == TOK_LANGLE && size() == 1 && at(0)->symbol == VECTOR) {
			return at(0)->concatenate();
		} else if (symbol == TOK_COMMA && size() == 2 && at(0)->isType() && at(1)->isValue()) {
			return at(0)->concatenate() + " " + at(1)->concatenate();
		} else if (isType()) {
			Type *type = getType(this);
			return "\e[33m" + std::string(*type) + "\e[0m";
			delete type;
		} else if (isValue()) {
			return "\e[1m" + *lexerInfo + "\e[0m";
		} else if (empty()) {
			return *lexerInfo;
		}

		std::stringstream out;
		for (ASTNode *child: children)
			out << *child->lexerInfo;
		return out.str();
	}

	int ASTNode::atoi() const {
		if (symbol == TOK_PVAR)
			return atoi(1);
		return parseLong(*lexerInfo);
	}

	int ASTNode::atoi(int offset) const {
		return parseLong(lexerInfo->substr(offset));
	}

	bool ASTNode::isType() const {
		return symbol == TOK_INTTYPE || symbol == TOK_FLOATTYPE || symbol == ARRAYTYPE || symbol == VECTORTYPE
		    || symbol == POINTERTYPE || symbol == TOK_VOID || symbol == FUNCTIONTYPE || symbol == TOK_STRUCTVAR;
	}

	bool ASTNode::isValue() const {
		return symbol == TOK_DECIMAL || symbol == TOK_FLOATING || symbol == TOK_BOOL || symbol == VECTOR
		    || symbol == TOK_PVAR || symbol == TOK_GVAR;
	}

	const char * ASTNode::getName() const {
		return Parser::getName(symbol);
	}

	void ASTNode::debug(int indent, bool is_last, bool suppress_line) const {
		if (indent == 0 && !suppress_line)
			std::cerr << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		for (int i = 0; i < indent; ++i) {
			std::cerr << "\e[2m";
			if (i == indent - 1)
				std::cerr << (is_last? "└── " : "├── ");
			else
				std::cerr << "│   ";
			std::cerr << "\e[0m";
		}

		std::cerr << style() << Parser::getName(symbol) << "\e[0;2m " << location << "\x1b[0;35m " << *lexerInfo;
		std::cerr << "\e[0m" << debugExtra() << "\n";
		for (ASTNode *child: children)
			child->debug(indent + 1, child == children.back());
	}

	std::string ASTNode::debugExtra() const {
		return "";
	}

	std::string ASTNode::style() const {
		return "\e[1m";
	}

	void ASTNode::destroy(std::initializer_list<ASTNode *> to_destroy) {
		for (ASTNode *node: to_destroy) {
			if (node)
				delete node;
		}
	}

	ASTNode * ASTNode::front() const {
		return children.front();
	}

	ASTNode * ASTNode::back() const {
		return children.back();
	}

	decltype(ASTNode::children)::iterator ASTNode::begin() {
		return children.begin();
	}

	decltype(ASTNode::children)::iterator ASTNode::end() {
		return children.end();
	}

	decltype(ASTNode::children)::const_iterator ASTNode::begin() const {
		return children.begin();
	}

	decltype(ASTNode::children)::const_iterator ASTNode::end() const {
		return children.end();
	}

	decltype(ASTNode::children)::const_iterator ASTNode::cbegin() const noexcept {
		return children.cbegin();
	}

	decltype(ASTNode::children)::const_iterator ASTNode::cend() const noexcept {
		return children.cend();
	}

	std::string ASTNode::extractName() const {
		if (symbol == TOK_PVAR || symbol == TOK_GVAR) {
			return lexerInfo->at(1) == '"'? lexerInfo->substr(2, lexerInfo->size() - 3) : lexerInfo->substr(1);
		} else if (symbol == TOK_CLASSVAR || symbol == TOK_STRUCTVAR || symbol == TOK_UNIONVAR) {
			if (lexerInfo->at(1) == '"')
				return lexerInfo->substr(2, lexerInfo->size() - 3);
			return lexerInfo->substr(1);
		} else if (symbol == TOK_CSTRING) {
			return lexerInfo->substr(2, lexerInfo->size() - 3);
		} else if (symbol == TOK_STRING || symbol == TOK_SOURCE_FILENAME) {
			return lexerInfo->substr(1, lexerInfo->size() - 2);
		}

		throw std::runtime_error("extractName() was called on an inappropriate symbol: " +
			std::string(Parser::getName(symbol)));
	}

	const std::string * ASTNode::extracted() const {
		return StringSet::intern(extractName());
	}
}