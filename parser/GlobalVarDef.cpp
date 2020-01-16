#include <sstream>

#include "GlobalVarDef.h"

namespace LL2W {
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

		if (unnamed_addr_) {
			if (*unnamed_addr_->lexerInfo == "unnamed_addr")
				unnamedAddr = UnnamedAddr::Unnamed;
			else if (*unnamed_addr_->lexerInfo == "local_unnamed_addr")
				unnamedAddr = UnnamedAddr::LocalUnnamed;
			delete unnamed_addr_;
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
		switch (unnamedAddr) {
			case UnnamedAddr::Unnamed: out << " unnamed_addr"; break;
			case UnnamedAddr::LocalUnnamed: out << " local_unnamed_addr"; break;
			default:;
		}

		out << "\e[0m";
		return out.str();
	}
}
