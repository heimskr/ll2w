#include "parser/EnumConversion.h"

namespace LL2W {
	Linkage getLinkage(llvm::GlobalValue::LinkageTypes type) {
		using enum Linkage;
		using enum llvm::GlobalValue::LinkageTypes;

		switch (type) {
			case ExternalLinkage: return External;
			case AvailableExternallyLinkage: return AvailableExternally;
			case LinkOnceAnyLinkage: return Linkonce;
			case LinkOnceODRLinkage: return LinkonceOdr;
			case WeakAnyLinkage: return Weak;
			case WeakODRLinkage: return WeakOdr;
			case AppendingLinkage: return Appending;
			case InternalLinkage: return Internal;
			case PrivateLinkage: return Private;
			case ExternalWeakLinkage: return ExternWeak;
			case CommonLinkage: return Common;
		}

		throw std::invalid_argument("Invalid linkage");
	}

	Visibility getVisibility(llvm::GlobalValue::VisibilityTypes type) {
		using enum Visibility;
		using enum llvm::GlobalValue::VisibilityTypes;

		switch (type) {
			case DefaultVisibility: return Default;
			case HiddenVisibility: return Hidden;
			case ProtectedVisibility: return Protected;
		}

		throw std::invalid_argument("Invalid visibility");
	}

	DllStorageClass getDllStorageClass(llvm::GlobalValue::DLLStorageClassTypes type) {
		using enum DllStorageClass;
		using enum llvm::GlobalValue::DLLStorageClassTypes;

		switch (type) {
			case DefaultStorageClass: return None;
			case DLLImportStorageClass: return Import;
			case DLLExportStorageClass: return Export;
		}

		throw std::invalid_argument("Invalid DLL storage class");
	}

	ThreadLocalMode getThreadLocalMode(llvm::GlobalValue::ThreadLocalMode type) {
		using enum ThreadLocalMode;
		using enum llvm::GlobalValue::ThreadLocalMode;

		switch (type) {
			case NotThreadLocal: return None;
			case GeneralDynamicTLSModel: return GeneralDynamic;
			case LocalDynamicTLSModel: return LocalDynamic;
			case InitialExecTLSModel: return InitialExec;
			case LocalExecTLSModel: return LocalExec;
		}

		throw std::invalid_argument("Invalid thread local mode");
	}

	UnnamedAddr getUnnamedAddr(llvm::GlobalValue::UnnamedAddr type) {
		using enum UnnamedAddr;
		using enum llvm::GlobalValue::UnnamedAddr;

		switch (type) {
			case None: return Default;
			case Local: return LocalUnnamed;
			case Global: return Unnamed;
		}

		throw std::invalid_argument("Invalid unnamed addr");
	}
}
