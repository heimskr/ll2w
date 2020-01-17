#include <cstdlib>
#include <iostream>
#include <sstream>

#include "FunctionHeader.h"
#include "Parser.h"
#include "StringSet.h"
#include "Types.h"

// TODO: reduce duplication of GlobalVarDef code

namespace LL2W {

	FunctionHeader::FunctionHeader(N linkage_, N visibility_, N dll_storage_class, N cconv_, N retattrs_, N type,
	                               N function_name, N function_args, N unnamed_addr, N fnattrs_):
		ASTNode(FUNCTION_HEADER, function_name->lexerInfo), arguments(dynamic_cast<FunctionArgs *>(function_args)) {
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

		adopt(fnattrs_);
	}
	
	std::string FunctionHeader::debugExtra() {
		std::stringstream out;
		out << " \e[0;33m" << std::string(*returnType);
		out << " \e[0;32m" << *name << "\e[36m";
		out << "\e[0;94m(";
		for (auto iter = arguments->arguments.begin(), end = arguments->arguments.end(); iter != end; ++iter) {
			if (iter != arguments->arguments.begin())
				out << ", ";
			const FunctionArgument &arg = *iter;
			out << std::string(*arg.type);
			for (ParAttr parattr: arg.parattrs)
				out << " " << parattr_map.at(parattr);
		}
		if (arguments->ellipse)
			out << (arguments->arguments.empty()? "..." : ", ...");
		out << ")\e[0;36m";
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
