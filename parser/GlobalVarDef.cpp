#include <cstdlib>
#include <sstream>

#include "GlobalVarDef.h"

namespace LL2W {
	GlobalVarDef::GlobalVarDef(ASTNode *gvar, ASTNode *linkage_, ASTNode *visibility_, ASTNode *dll_storage_class,
	                           ASTNode *thread_local_, ASTNode *unnamed_addr, ASTNode *addrspace_,
	                           ASTNode *externally_initialized, ASTNode *global_or_constant, ASTNode *type_,
	                           ASTNode *initial_value, ASTNode *gdef_extras): ASTNode(TOK_GVAR, gvar->lexerInfo) {
		if (linkage_) {
			const std::string &link = *linkage_->lexerInfo;
			for (const std::pair<Linkage, std::string> &pair: linkage_map) {
				if (link == pair.second) {
					linkage = pair.first;
					break;
				}
			}
			delete linkage_;
		}

		if (visibility_) {
			visibility = *visibility_->lexerInfo == "hidden"? Visibility::Hidden :
				(*visibility_->lexerInfo == "protected"? Visibility::Protected : Visibility::Default);
			delete visibility_;
		}

		if (dll_storage_class) {
			dllStorageClass = *dll_storage_class->lexerInfo == "dllimport"?
				DllStorageClass::Import : DllStorageClass::Export;
			delete dll_storage_class;
		}

		if (thread_local_) {
			const std::string &tl = *thread_local_->at(0)->lexerInfo;
			if (tl == "localdynamic")
				threadLocal = ThreadLocal::LocalDynamic;
			else if (tl == "initialexec")
				threadLocal = ThreadLocal::InitialExec;
			else if (tl == "localexec")
				threadLocal = ThreadLocal::LocalExec;
			delete thread_local_;
		}

		if (unnamed_addr) {
			if (*unnamed_addr->lexerInfo == "unnamed_addr")
				unnamedAddr = UnnamedAddr::Unnamed;
			else if (*unnamed_addr->lexerInfo == "local_unnamed_addr")
				unnamedAddr = UnnamedAddr::LocalUnnamed;
			delete unnamed_addr;
		}

		if (addrspace_) {
			addrspace = atoi(addrspace_->children.front()->lexerInfo->c_str());
			delete addrspace_;
		}

		if (externally_initialized) {
			externallyInitialized = true;
			delete externally_initialized;
		}

		if (global_or_constant) {
			isConstant = *global_or_constant->lexerInfo == "constant";
			delete global_or_constant;
		}

		type = getType(type_);
		initialValue = initial_value;
	}

	std::string GlobalVarDef::debugExtra() const {
		std::stringstream out;
		out << "\e[36m";

		if (linkage != Linkage::Default)
			out << " " << linkage_map.at(linkage);
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
		switch (unnamedAddr) {
			case UnnamedAddr::Unnamed: out << " unnamed_addr"; break;
			case UnnamedAddr::LocalUnnamed: out << " local_unnamed_addr"; break;
			default:;
		}
		if (addrspace != -1)
			out << " addrspace(" << addrspace << ")";
		if (externallyInitialized)
			out << " externally_initialized";
		out << (isConstant? " constant" : " global");
		out << " \e[0;32m" << std::string(*type);
		out << "\e[0m";
		if (initialValue && initialValue->symbol == TOK_CSTRING)
			out << " \e[34mc\e[33m" << initialValue->lexerInfo->substr(1) << "\e[0m";
		return out.str();
	}
}
