#ifndef PARSER_GLOBALVARDEF_H_
#define PARSER_GLOBALVARDEF_H_

#include "ASTNode.h"
#include "Lexer.h"

namespace LL2W {
	enum class Linkage {
		Default, Private, Appending, AvailableExternally, Weak, Linkonce, ExternWeak, LinkonceOdr, WeakOdr, External,
		Common, Internal
	};
	enum class Visibility {Default, Hidden, Protected};
	enum class DllStorageClass {None, Import, Export};
	enum class ThreadLocal {None, LocalDynamic, InitialExec, LocalExec};
	enum class UnnamedAddr {Default, Unnamed, LocalUnnamed};

	struct GlobalVarDef: public ASTNode {
		Linkage linkage = Linkage::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		ThreadLocal threadLocal = ThreadLocal::None;
		UnnamedAddr unnamedAddr = UnnamedAddr::Default;

		GlobalVarDef(ASTNode *gvar_, ASTNode *linkage_, ASTNode *visibility_, ASTNode *dll_storage_class_,
		             ASTNode *thread_local_, ASTNode *unnamed_addr_, ASTNode *addrspace_,
		             ASTNode *externally_initialized_, ASTNode *global_or_constant_, ASTNode *type_,
		             ASTNode *initial_value_, ASTNode *gdef_extras_);

		std::string debugExtra() override;
	};
}

#endif
