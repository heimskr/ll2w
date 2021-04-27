#pragma once

#include "ASTNode.h"
#include "Enums.h"
#include "Lexer.h"
#include "Types.h"
#include "Constant.h"

namespace LL2W {
	struct GlobalVarDef: public ASTNode {
		Linkage linkage = Linkage::Default;
		Preemption preemption = Preemption::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		ThreadLocal threadLocal = ThreadLocal::None;
		UnnamedAddr unnamedAddr = UnnamedAddr::Default;
		int addrspace = -1;
		bool externallyInitialized = false;
		bool isConstant = false; // Global if false, constant if true

		// Global variable definitions sometimes include a full constant, but they can also include just a type, e.g.
		//     @foo = external unnamed_addr constant { [3 x i8*] }, align 8
		ConstantPtr constant = nullptr;
		TypePtr type = nullptr;

		const std::string *section = nullptr;
		const std::string *comdat = nullptr;

		using N = ASTNode *;
		GlobalVarDef(N gvar, N linkage_, N preemption_, N visibility_, N dll_storage_class, N thread_local_,
		             N unnamed_addr, N addrspace_, N externally_initialized_, N global_or_constant_, N type_or_constant,
		             N gdef_extras_);

		std::string debugExtra() const override;
		std::string style() const override { return "\e[32m"; }
	};
}
