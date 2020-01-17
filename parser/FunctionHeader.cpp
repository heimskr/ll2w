#include <cstdlib>
#include <iostream>
#include <sstream>

#include "FunctionHeader.h"
#include "Parser.h"
#include "StringSet.h"
#include "Types.h"

// TODO: reduce duplication of GlobalVarDef code

namespace LL2W {
	std::unordered_map<CConv, std::string> cconv_map {
		{CConv::Default, "default"}, {CConv::ccc, "ccc"}, {CConv::cxx_fast_tlscc, "cxx_fast_tlscc"},
		{CConv::fastcc, "fastcc"}, {CConv::ghccc, "ghccc"}, {CConv::swiftcc, "swiftcc"},
		{CConv::preserve_allcc, "preserve_allcc"}, {CConv::preserve_mostcc, "preserve_mostcc"},
		{CConv::x86_vectorcallcc, "x86_vectorcallcc"}, {CConv::cc10, "cc10"}, {CConv::cc11, "cc11"},
		{CConv::arm_apcscc, "arm_apcscc"}, {CConv::coldcc, "coldcc"}, {CConv::webkit_jscc, "webkit_jscc"},
		{CConv::cc64, "cc64"}, {CConv::cc65, "cc65"}, {CConv::cc66, "cc66"}, {CConv::ptx_device, "ptx_device"},
		{CConv::x86_stdcallcc, "x86_stdcallcc"}, {CConv::cc67, "cc67"}, {CConv::cc68, "cc68"}, {CConv::cc69, "cc69"},
		{CConv::cc70, "cc70"}, {CConv::cc1023, "cc1023"}, {CConv::anyregcc, "anyregcc"}, {CConv::cc71, "cc71"},
		{CConv::cc72, "cc72"}, {CConv::cc75, "cc75"}, {CConv::msp430_intrcc, "msp430_intrcc"},
		{CConv::ptx_kernel, "ptx_kernel"}, {CConv::cc76, "cc76"}, {CConv::cc77, "cc77"}, {CConv::cc78, "cc78"},
		{CConv::spir_func, "spir_func"}, {CConv::x86_64_win64cc, "x86_64_win64cc"}, {CConv::cc79, "cc79"},
		{CConv::cc80, "cc80"}, {CConv::arm_aapcs_vfpcc, "arm_aapcs_vfpcc"}, {CConv::intel_ocl_bicc, "intel_ocl_bicc"},
		{CConv::x86_64_sysvcc, "x86_64_sysvcc"}, {CConv::x86_fastcallcc, "x86_fastcallcc"},
		{CConv::x86_thiscallcc, "x86_thiscallcc"}, {CConv::arm_aapcscc, "arm_aapcscc"},
		{CConv::spir_kernel, "spir_kernel"}};
	
	std::unordered_map<RetAttr, std::string> retattr_map {
		{RetAttr::Zeroext, "zeroext"}, {RetAttr::Signext, "signext"}, {RetAttr::Inreg, "inreg"},
		{RetAttr::Noalias, "noalias"}, {RetAttr::Nonnull, "nonnull"}};

	FunctionHeader::FunctionHeader(N linkage_, N visibility_, N dll_storage_class, N cconv_, N retattrs_, N type,
	                               N function_name, N function_args, N unnamed_addr, N fnattrs_):
	                               ASTNode(FUNCTION_HEADER, function_name->lexerInfo) {
		name = StringSet::intern(function_name->extractName());

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

		if (cconv_) {
			const std::string &cc = *cconv_->lexerInfo;
			for (const std::pair<CConv, std::string> &pair: cconv_map) {
				if (cc == pair.second) {
					cconv = pair.first;
					break;
				}
			}
			delete cconv_;
		}

		if (retattrs_) {
			for (ASTNode *retattr: retattrs_->children) {
				const std::string *str = retattr->lexerInfo;
				if (retattr->symbol == TOK_RETATTR) {
					if (*str == "zeroext") retattrs.insert(RetAttr::Zeroext);
					else if (*str == "inreg") retattrs.insert(RetAttr::Inreg);
					else if (*str == "noalias") retattrs.insert(RetAttr::Noalias);
					else if (*str == "signext") retattrs.insert(RetAttr::Signext);
					else if (*str == "nonnull") retattrs.insert(RetAttr::Nonnull);
					else throw std::runtime_error("Unrecognized retattr: " + *str);
				} else if (retattr->symbol == TOK_DEREF) {
					Deref new_deref;
					if (*str == "dereferenceable") new_deref = Deref::Dereferenceable;
					else if (*str == "dereferenceable_or_null") new_deref = Deref::DereferenceableOrNull;
					else throw std::runtime_error("Unrecognized deref: " + *str);
					int bytes = atoi(retattr->at(0)->lexerInfo->c_str());
					if (deref == Deref::DereferenceableOrNull && new_deref == Deref::Dereferenceable) {
						// If dereferenceable_or_null(x) -> dereferenceable(y), set bytes to max(x, y).
						if (dereferenceableBytes < bytes)
							dereferenceableBytes = bytes;
						deref = new_deref;
					} else if (deref == Deref::Default) {
						deref = new_deref;
						dereferenceableBytes = bytes;
					}
				}
			}
			delete retattrs_;
		}

		returnType = getType(type);

		adopt(function_args);
		argumentTypes.reserve(function_args->children.size());
		for (ASTNode *child: function_args->children) {
			// Each function argument can have PARATTR_LIST and TOK_PVAR/TOK_PSTRING/TOK_PDECIMAL children at the end.
			argumentTypes.push_back(getType(child));
		}
	}
	
	std::string FunctionHeader::debugExtra() {
		std::stringstream out;
		out << " \e[0;33m" << std::string(*returnType);
		out << " \e[0;32m" << *name << "\e[36m";
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
		if (cconv != CConv::Default)
			out << " " << cconv_map.at(cconv);
		for (RetAttr retattr: retattrs)
			out << " " << retattr_map.at(retattr);
		if (deref == Deref::Dereferenceable)
			out << " dereferenceable(" << dereferenceableBytes << ")";
		else if (deref == Deref::DereferenceableOrNull)
			out << " dereferenceable_or_null(" << dereferenceableBytes << ")";
		out << "\e[0m";
		return out.str();
	}
}
