#include "parser/EnumConversion.h"
#include "parser/GlobalVarDef.h"
#include "parser/Parser.h"

#include <llvm/IR/GlobalVariable.h>

#include <iostream>
#include <cstdlib>
#include <print>
#include <sstream>

namespace LL2W {
	GlobalVarDef::GlobalVarDef(const llvm::GlobalVariable &llvm_var) {
		name = llvm_var.getName().str();
		linkage = getLinkage(llvm_var.getLinkage());
		preemption = llvm_var.isDSOLocal()? Preemption::DsoLocal : Preemption::Default;
		visibility = getVisibility(llvm_var.getVisibility());
		dllStorageClass = getDllStorageClass(llvm_var.getDLLStorageClass());
		threadLocal = getThreadLocalMode(llvm_var.getThreadLocalMode());
		unnamedAddr = getUnnamedAddr(llvm_var.getUnnamedAddr());
		addrspace = static_cast<int>(llvm_var.getAddressSpace());
		externallyInitialized = llvm_var.isExternallyInitialized();
		isConstant = llvm_var.isConstant();
		if (llvm_var.hasInitializer()) {
			constant = Constant::fromLLVM(*llvm_var.getInitializer());
		} else {
			constant = Constant::make(std::make_shared<OpaqueType>(), GlobalValue::make(llvm_var.getName().str()));
		}
		type = Type::fromLLVM(*llvm_var.getValueType());
	}

	GlobalVarDef::GlobalVarDef(ASTNode *gvar, ASTNode *linkage_, ASTNode *preemption_, ASTNode *visibility_,
	                           ASTNode *dll_storage_class, ASTNode *thread_local_, ASTNode *unnamed_addr,
	                           ASTNode *addrspace_, ASTNode *externally_initialized, ASTNode *global_or_constant,
	                           ASTNode *type_or_constant, ASTNode *gdef_extras):
	                           ASTNode(llvmParser, LLVM_GLOBAL_DEF, gvar->lexerInfo) {
		delete gvar;

		if (linkage_) {
			const std::string &link = *linkage_->lexerInfo;
			for (const std::pair<const Linkage, std::string> &pair: linkage_map) {
				if (link == pair.second) {
					linkage = pair.first;
					break;
				}
			}
			delete linkage_;
		}

		if (preemption_) {
			if (*preemption_->lexerInfo == "dso_preemptable")
				preemption = Preemption::DsoPreemptable;
			else if (*preemption_->lexerInfo == "dso_local")
				preemption = Preemption::DsoLocal;
			else
				throw std::runtime_error("Invalid preemption in GlobalVarDef: \"" + *preemption_->lexerInfo + "\"");
			delete preemption_;
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
				threadLocal = ThreadLocalMode::LocalDynamic;
			else if (tl == "initialexec")
				threadLocal = ThreadLocalMode::InitialExec;
			else if (tl == "localexec")
				threadLocal = ThreadLocalMode::LocalExec;
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
			addrspace = addrspace_->children.front()->atoi();
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

		if (type_or_constant->symbol == LLVM_CONSTANT) {
			constant = std::make_shared<Constant>(type_or_constant);
		} else {
			type = getType(type_or_constant);
		}
		delete type_or_constant;

		for (ASTNode *extra: *gdef_extras) {
			if (extra->symbol == LLVMTOK_SECTION) {
				section = extra->at(0)->lexerInfo;
			} else if (extra->symbol == LLVMTOK_COMDAT) {
				if (!extra->empty()) {
					const std::string *str = extra->at(0)->lexerInfo;
					if (str->empty() || str->front() != '$') {
						llvmerror("Comdat expected to begin with \"$\"");
					}
					comdat = str;
				}
			} else if (!extra) {
				std::cout << "\e[91m!extra\e[0m\n";
			} else {
				// TODO
				// std::cout << "[" << Parser::getName(extra->symbol) << "]\n";
				// extra->debug();
			}
		}
		delete gdef_extras;
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
			case ThreadLocalMode::LocalDynamic: out << " localdynamic"; break;
			case ThreadLocalMode::InitialExec:  out << " initialexec"; break;
			case ThreadLocalMode::LocalExec:    out << " localexec"; break;
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
		// out << "\e[0m " << std::string(*type);
		if (constant)
			out << " " << std::string(*constant);
		else
			out << " " << std::string(*type);
		// if (initialValue) {
		// 	if (initialValue->symbol == TOK_CSTRING)
		// 		out << " \e[34mc\e[33m" << initialValue->lexerInfo->substr(1) << "\e[0m";
		// }
		return out.str();
	}
}
