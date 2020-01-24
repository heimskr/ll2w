#ifndef PARSER_GLOBALVARDEF_H_
#define PARSER_GLOBALVARDEF_H_

#include "ASTNode.h"
#include "Enums.h"
#include "Lexer.h"
#include "Types.h"
#include "Constant.h"

namespace LL2W {
	struct GlobalVarDef: public ASTNode {
		Linkage linkage = Linkage::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		ThreadLocal threadLocal = ThreadLocal::None;
		UnnamedAddr unnamedAddr = UnnamedAddr::Default;
		int addrspace = -1;
		bool externallyInitialized = false;
		bool isConstant = false; // Global if false, constant if true
		Constant *constant;
		const std::string *section = nullptr;
		const std::string *comdat = nullptr;

		using N = ASTNode *;
		GlobalVarDef(N gvar, N linkage_, N visibility_, N dll_storage_class, N thread_local_, N unnamed_addr,
		             N addrspace_, N externally_initialized_, N global_or_constant_, N constant_, N gdef_extras_);

		~GlobalVarDef() { delete constant; }

		std::string debugExtra() const override;
		virtual std::string style() const override { return "\e[32m"; }
	};
}

#endif
