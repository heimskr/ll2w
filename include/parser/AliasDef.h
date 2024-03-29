#pragma once

#include "ASTNode.h"
#include "Enums.h"
#include "Types.h"

namespace LL2W {
	struct AliasDef: public ASTNode {
		const std::string *name = nullptr;
		Linkage linkage = Linkage::Default;
		Preemption preemption = Preemption::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		ThreadLocal threadLocal = ThreadLocal::None;
		UnnamedAddr unnamedAddr = UnnamedAddr::Default;
		TypePtr type, ptrType;
		const std::string *aliasTo = nullptr;

		AliasDef(ASTNode *gvar, ASTNode *linkage_, ASTNode *preemption_, ASTNode *visibility_,
		         ASTNode *dll_storage_class, ASTNode *thread_local_, ASTNode *unnamed_addr, ASTNode *type_,
		         ASTNode *value_node);

		std::string debugExtra() const override;
	};
}
