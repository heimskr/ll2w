#pragma once

#include <memory>
#include <unordered_set>

#include "FunctionArgs.h"
#include "GlobalVarDef.h"
#include "Constant.h"

namespace LL2W {
	struct FunctionHeader: public ASTNode {
		const std::string *name;
		Linkage linkage = Linkage::Default;
		Preemption preemption = Preemption::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		CConv cconv = CConv::ccc;
		Deref deref = Deref::Default;
		std::unordered_set<RetAttr> retattrs;
		int dereferenceableBytes = -1;
		TypePtr returnType;
		std::shared_ptr<FunctionArgs> arguments;
		UnnamedAddr unnamedAddr = UnnamedAddr::Default;
		std::unordered_set<FnAttr> fnattrs;
		int align = -1;
		int fnattrsIndex = -1; // When there's /#\d+/ instead of an inline list of function attributes
		ConstantPtr personality;
		const std::string *section = nullptr, *comdat = nullptr;

		using N = ASTNode *;
		FunctionHeader();
		FunctionHeader(const llvm::Function &);
		FunctionHeader(N _linkage, N _preemption, N _visibility, N _dll_storage_class, N _cconv, N _retattrs, N type,
		               N function_name, N function_args, N unnamed_addr, N _fnattrs, N _section, N _comdat, N _align,
		               N _personality, N debug);

		std::string debugExtra() const override;
		virtual std::string style() const override { return "\e[38;5;202m"; }
	};
}
