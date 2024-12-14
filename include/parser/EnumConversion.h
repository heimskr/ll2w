#pragma once

#include "parser/Enums.h"

#include <llvm/IR/GlobalValue.h>

namespace LL2W {
	Linkage getLinkage(llvm::GlobalValue::LinkageTypes);
	Visibility getVisibility(llvm::GlobalValue::VisibilityTypes);
	DllStorageClass getDllStorageClass(llvm::GlobalValue::DLLStorageClassTypes);
	ThreadLocalMode getThreadLocalMode(llvm::GlobalValue::ThreadLocalMode);
	UnnamedAddr getUnnamedAddr(llvm::GlobalValue::UnnamedAddr);
}