#ifndef PARSER_FUNCTIONHEADER_H_
#define PARSER_FUNCTIONHEADER_H_

#include <unordered_set>

#include "FunctionArgs.h"
#include "GlobalVarDef.h"
#include "Constant.h"

namespace LL2W {
	struct FunctionHeader: public ASTNode {
		const std::string *name;
		Linkage linkage = Linkage::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		CConv cconv = CConv::Default;
		Deref deref = Deref::Default;
		std::unordered_set<RetAttr> retattrs;
		int dereferenceableBytes = -1; // TODO: separate values for dereferenceable and dereferenceable_or_null?
		Type *returnType;
		FunctionArgs *arguments;
		UnnamedAddr unnamedAddr = UnnamedAddr::Default;
		std::unordered_set<FnAttr> fnattrs;
		int align = -1;
		int fnattrsIndex = -1; // When there's /#\d+/ instead of an inline list of function attributes
		Constant *personality = nullptr;
		
		using N = ASTNode *;
		FunctionHeader(N _linkage, N _visibility, N _dll_storage_class, N _cconv, N _retattrs, N type, N function_name,
		               N function_args, N unnamed_addr, N _fnattrs, N _align, N _personality);
		~FunctionHeader();

		std::string debugExtra() const override;
		virtual std::string style() const override { return "\e[38;5;202m"; }
	};
}

#endif
