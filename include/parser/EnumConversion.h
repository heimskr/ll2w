#pragma once

#include "parser/Enums.h"

#include <llvm/IR/Attributes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Instructions.h>

#include <string_view>
#include <unordered_set>

namespace llvm {
	class FastMathFlags;
}

namespace LL2W {
	Linkage getLinkage(llvm::GlobalValue::LinkageTypes);
	Visibility getVisibility(llvm::GlobalValue::VisibilityTypes);
	DllStorageClass getDllStorageClass(llvm::GlobalValue::DLLStorageClassTypes);
	ThreadLocalMode getThreadLocalMode(llvm::GlobalValue::ThreadLocalMode);
	UnnamedAddr getUnnamedAddr(llvm::GlobalValue::UnnamedAddr);
	TailCallKind getTailCallKind(llvm::CallInst::TailCallKind);
	TailCallKind getTailCallKind(std::string_view);
	std::unordered_set<Fastmath> getFastmath(llvm::FastMathFlags);
	CConv getCConv(unsigned);
	CConv getCConv(std::string_view);
	RetAttr getRetAttr(llvm::Attribute::AttrKind);
	Ordering getOrdering(llvm::AtomicOrdering);
	IcmpCond getIcmpCond(llvm::CmpInst::Predicate);
}