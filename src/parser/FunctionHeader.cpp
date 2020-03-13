#include <cstdlib>
#include <iostream>
#include <sstream>

#include "parser/FunctionHeader.h"
#include "parser/Parser.h"
#include "parser/StringSet.h"
#include "parser/Types.h"

// TODO: reduce duplication of GlobalVarDef code

namespace LL2W {
	FunctionHeader::FunctionHeader(N _linkage, N _visibility, N _dll_storage_class, N _cconv, N _retattrs, N type,
	                               N function_name, N function_args, N unnamed_addr, N _fnattrs, N _align,
	                               N _personality):
		ASTNode(FUNCTION_HEADER, function_name->lexerInfo), arguments(dynamic_cast<FunctionArgs *>(function_args)) {
		name = StringSet::intern(function_name->extractName());

		if (_linkage) {
			const std::string &link = *_linkage->lexerInfo;
			for (const std::pair<Linkage, std::string> &pair: linkage_map) {
				if (link == pair.second) {
					linkage = pair.first;
					break;
				}
			}
			delete _linkage;
		}

		if (_visibility) {
			visibility = *_visibility->lexerInfo == "hidden"? Visibility::Hidden :
				(*_visibility->lexerInfo == "protected"? Visibility::Protected : Visibility::Default);
			delete _visibility;
		}

		if (_dll_storage_class) {
			dllStorageClass = *_dll_storage_class->lexerInfo == "dllimport"?
				DllStorageClass::Import : DllStorageClass::Export;
			delete _dll_storage_class;
		}

		if (_cconv) {
			const std::string &cc = *_cconv->lexerInfo;
			for (const std::pair<CConv, std::string> &pair: cconv_map) {
				if (cc == pair.second) {
					cconv = pair.first;
					break;
				}
			}
			delete _cconv;
		}

		if (_retattrs) {
			for (ASTNode *retattr: *_retattrs) {
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
					int bytes = retattr->at(0)->atoi();
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
			delete _retattrs;
		}

		returnType = getType(type);
		delete type;

		if (unnamed_addr) {
			const std::string &uatype = *unnamed_addr->lexerInfo;
			if (uatype == "local_unnamed_addr")
				unnamedAddr = UnnamedAddr::LocalUnnamed;
			else if (uatype == "unnamed_addr")
				unnamedAddr = UnnamedAddr::Unnamed;
			else throw std::runtime_error("Invalid lexerinfo for unnamed_addr: " + uatype);
			delete unnamed_addr;
		}

		if (_fnattrs->symbol == TOK_DECIMAL) {
			fnattrsIndex = _fnattrs->atoi();
		} else if (_fnattrs->symbol == FNATTR_LIST) {
			for (ASTNode *fnattr: _fnattrs->children) {
				const std::string &fnattr_name = *fnattr->lexerInfo;
				for (const std::pair<FnAttr, std::string> &pair: fnattr_map) {
					if (fnattr_name == pair.second) {
						fnattrs.insert(pair.first);
						break;
					}
				}
			}
			delete _fnattrs;
		} else {
			throw std::runtime_error("Bad symbol for fnattrs node: " + std::string(Parser::getName(_fnattrs->symbol)));
		}

		if (_align) {
			align = _align->at(0)->atoi();
			delete _align;
		}

		if (_personality) {
			personality = std::make_shared<Constant>(_personality->at(0));
			delete _personality;
		}
	}

	std::string FunctionHeader::debugExtra() const {
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
			if (arg.originalName)
				out << " " << *arg.originalName;
		}
		if (arguments->ellipsis)
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
		if (unnamedAddr == UnnamedAddr::Unnamed)
			out << " unnamed_addr";
		else if (unnamedAddr == UnnamedAddr::LocalUnnamed)
			out << " local_unnamed_addr";
		for (FnAttr fnattr: fnattrs)
			out << " " << fnattr_map.at(fnattr);
		if (fnattrsIndex != -1)
			out << " #" << fnattrsIndex;
		if (personality)
			out << " personality " << std::string(*personality);
		out << "\e[0m";
		return out.str();
	}
}
