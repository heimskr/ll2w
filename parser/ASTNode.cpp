#include <iostream>
#include <sstream>

#include "ASTNode.h"
#include "StringSet.h"
#include "Parser.h"
#include "Lexer.h"

namespace LL2W {
	Location::operator std::string() const {
		return *filename() + ":" + std::to_string(line + 1) + ":" + std::to_string(column);
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

	void ASTNode::debug(int indent, bool is_last) {
		for (int i = 0; i < indent; ++i) {
			std::cerr << "\e[2m";
			if (i == indent - 1)
				std::cerr << (is_last? "└── " : "├── ");
			else
				std::cerr << "│   ";
			std::cerr << "\e[0m";
		}

		std::cerr << "\e[1m" << Parser::getName(symbol) << "\e[0;2m " << location << "\x1b[0;35m " << *lexerInfo;
		std::cerr << "\e[0m" << debugExtra() << "\n";
		for (ASTNode *child: children)
			child->debug(indent + 1, child == children.back());
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
		return " \e[36m" + std::string(distinct? "" : "not ") + "distinct\e[0m";
	}

	GlobalVarDef::GlobalVarDef(ASTNode *gvar_, ASTNode *linkage_, ASTNode *visibility_, ASTNode *dll_storage_class_,
	                           ASTNode *thread_local_, ASTNode *unnamed_addr_, ASTNode *addrspace_,
	                           ASTNode *externally_initialized_, ASTNode *global_or_constant_, ASTNode *type_,
	                           ASTNode *initial_value_, ASTNode *gdef_extras_): ASTNode(TOK_GVAR, gvar_->lexerInfo) {
		if (linkage_) {
			const std::string &link = *linkage_->lexerInfo;
			if (link == "private")
				linkage = Linkage::Private;
			else if (link == "appending")
				linkage = Linkage::Appending;
			else if (link == "available_externally")
				linkage = Linkage::AvailableExternally;
			else if (link == "weak")
				linkage = Linkage::Weak;
			else if (link == "linkonce")
				linkage = Linkage::Linkonce;
			else if (link == "extern_weak")
				linkage = Linkage::ExternWeak;
			else if (link == "linkonce_odr")
				linkage = Linkage::LinkonceOdr;
			else if (link == "weak_odr")
				linkage = Linkage::WeakOdr;
			else if (link == "external")
				linkage = Linkage::External;
			else if (link == "common")
				linkage = Linkage::Common;
			else if (link == "internal")
				linkage = Linkage::Internal;
			delete linkage_;
		}

		if (visibility_) {
			visibility = *visibility_->lexerInfo == "hidden"? Visibility::Hidden :
				(*visibility_->lexerInfo == "protected"? Visibility::Protected : Visibility::Default);
			delete visibility_;
		}

		if (dll_storage_class_) {
			dllStorageClass = *dll_storage_class_->lexerInfo == "dllimport"?
				DllStorageClass::Import : DllStorageClass::Export;
			delete dll_storage_class_;
		}

		if (thread_local_) {
			const std::string &tl = *thread_local_->children[0]->lexerInfo;
			if (tl == "localdynamic")
				threadLocal = ThreadLocal::LocalDynamic;
			else if (tl == "initialexec")
				threadLocal = ThreadLocal::InitialExec;
			else if (tl == "localexec")
				threadLocal = ThreadLocal::LocalExec;
			delete thread_local_;
		}
	}

	std::string GlobalVarDef::debugExtra() {
		std::stringstream out;
		out << "\e[36m";
		switch (linkage) {
			case Linkage::Default:             out << " default"; break;
			case Linkage::Private:             out << " private"; break;
			case Linkage::Appending:           out << " appending"; break;
			case Linkage::AvailableExternally: out << " available_externally"; break;
			case Linkage::Weak:                out << " weak"; break;
			case Linkage::Linkonce:            out << " linkonce"; break;
			case Linkage::ExternWeak:          out << " extern_weak"; break;
			case Linkage::LinkonceOdr:         out << " linkonce_odr"; break;
			case Linkage::WeakOdr:             out << " weak_odr"; break;
			case Linkage::External:            out << " external"; break;
			case Linkage::Common:              out << " common"; break;
			case Linkage::Internal:            out << " internal"; break;
		}
		switch (visibility) {
			case Visibility::Hidden:    out << " hidden"; break;
			case Visibility::Protected: out << " protected"; break;
			default:;
		}
		switch (dllStorageClass) {
			case DllStorageClass::Import: out << " import"; break;
			case DllStorageClass::Export: out << " export"; break;
			default:;
		}
		switch (threadLocal) {
			case ThreadLocal::LocalDynamic: out << " localdynamic"; break;
			case ThreadLocal::InitialExec:  out << " initialexec"; break;
			case ThreadLocal::LocalExec:    out << " localexec"; break;
			default:;
		}

		out << "\e[0m";
		return out.str();
	}
}
