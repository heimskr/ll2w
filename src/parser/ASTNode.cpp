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

	ASTNode::ASTNode(Parser &parser_, int sym, const Location &loc, const char *info) {
		parser = &parser_;
		symbol = sym;
		location = loc;
		lexerInfo = StringSet::intern(info);
	}

	ASTNode::ASTNode(Parser &parser_, int sym, const Location &loc, const std::string *info):
		parser(&parser_), symbol(sym), location(loc), lexerInfo(info) {}

	ASTNode::ASTNode(Parser &parser_, int sym, const std::string *info):
		parser(&parser_), symbol(sym), location(llvmLexer.location), lexerInfo(info) {}

	ASTNode::ASTNode(Parser &parser_, int sym, const char *info) {
		parser = &parser_;
		symbol = sym;
		location = llvmLexer.location;
		lexerInfo = StringSet::intern(info);
	}

	ASTNode::ASTNode(Parser &parser_, int sym, const Location &loc): ASTNode(parser_, sym, loc, "") {}

	ASTNode::ASTNode(Parser &parser_, int sym): ASTNode(parser_, sym, "") {}

	ASTNode::ASTNode(Parser &parser_, int sym, ASTNode *node, const char *info):
			ASTNode(parser_, sym, node->location, info) {
		adopt(node);
	}

	ASTNode::ASTNode(Parser &parser_, int sym, ASTNode *node, const std::string *info):
			ASTNode(parser_, sym, node->location, info) {
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

	ASTNode * ASTNode::setDebug(int new_index) {
		debugIndex = new_index;
		return this;
	}

	ASTNode * ASTNode::setDebug(ASTNode *node) {
		if (node) {
			debugIndex = node->front()->atoi();
			delete node;
		}
		return this;
	}

	std::string ASTNode::concatenate() const {
		if (symbol == LLVM_VECTOR) {
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
		} else if (symbol == LLVMTOK_LANGLE && size() == 1 && at(0)->symbol == LLVM_VECTOR) {
			return at(0)->concatenate();
		} else if (symbol == LLVMTOK_COMMA && size() == 2 && at(0)->isType() && at(1)->isValue()) {
			return at(0)->concatenate() + " " + at(1)->concatenate();
		} else if (isType()) {
			return "\e[33m" + std::string(*getType(this)) + "\e[0m";
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

	long ASTNode::atoi() const {
		if (symbol == LLVMTOK_PVAR || symbol == LLVMTOK_INTBANG)
			return atoi(1);
		if (lexerInfo->substr(0, 2) == "0x")
			return Util::parseLong(lexerInfo->substr(2), 16);
		return Util::parseLong(*lexerInfo);
	}

	long ASTNode::atoi(int offset) const {
		return Util::parseLong(lexerInfo->substr(offset));
	}

	bool ASTNode::isType() const {
		return symbol == LLVMTOK_INTTYPE   || symbol == LLVMTOK_FLOATTYPE || symbol == LLVM_ARRAYTYPE
		    || symbol == LLVM_VECTORTYPE   || symbol == LLVM_POINTERTYPE  || symbol == LLVMTOK_VOID
		    || symbol == LLVM_FUNCTIONTYPE || symbol == LLVMTOK_STRUCTVAR;
	}

	bool ASTNode::isValue() const {
		return symbol == LLVMTOK_DECIMAL || symbol == LLVMTOK_FLOATING || symbol == LLVMTOK_BOOL || symbol == LLVM_VECTOR
		    || symbol == LLVMTOK_PVAR || symbol == LLVMTOK_GVAR;
	}

	const char * ASTNode::getName() const {
		return parser->getName(symbol);
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

		std::cerr << style() << parser->getName(symbol) << "\e[0;2m " << location << "\x1b[0;35m " << *lexerInfo;
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
		if (symbol == LLVMTOK_PVAR || symbol == LLVMTOK_GVAR) {
			return lexerInfo->at(1) == '"'? lexerInfo->substr(2, lexerInfo->size() - 3) : lexerInfo->substr(1);
		} else if (symbol == LLVMTOK_CLASSVAR || symbol == LLVMTOK_STRUCTVAR || symbol == LLVMTOK_UNIONVAR) {
			if (lexerInfo->at(1) == '"')
				return lexerInfo->substr(2, lexerInfo->size() - 3);
			return lexerInfo->substr(1);
		} else if (symbol == LLVMTOK_CSTRING) {
			return lexerInfo->substr(2, lexerInfo->size() - 3);
		} else if (symbol == LLVMTOK_STRING || symbol == LLVMTOK_SOURCE_FILENAME) {
			return lexerInfo->substr(1, lexerInfo->size() - 2);
		}

		throw std::runtime_error("extractName() was called on an inappropriate symbol: " +
			std::string(parser->getName(symbol)));
	}

	const std::string * ASTNode::extracted() const {
		return StringSet::intern(extractName());
	}
}
