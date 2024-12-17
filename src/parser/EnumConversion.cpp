#include "parser/EnumConversion.h"

#include <llvm/IR/CallingConv.h>
#include <llvm/IR/FMF.h>

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

	TailCallKind getTailCallKind(llvm::CallInst::TailCallKind kind) {
		using enum TailCallKind;
		using enum llvm::CallInst::TailCallKind;

		switch (kind) {
			case TCK_None: return None;
			case TCK_Tail: return Tail;
			case TCK_MustTail: return MustTail;
			case TCK_NoTail: return NoTail;
		}

		throw std::invalid_argument("Invalid tail call kind");
	}

	TailCallKind getTailCallKind(std::string_view kind) {
		using enum TailCallKind;

		if (kind.empty() || kind == "none") {
			return None;
		}

		if (kind == "tail") {
			return Tail;
		}

		if (kind == "musttail") {
			return MustTail;
		}

		if (kind == "notail") {
			return NoTail;
		}

		throw std::invalid_argument("Invalid tail call kind");
	}

	std::unordered_set<Fastmath> getFastmath(llvm::FastMathFlags flags) {
		using enum Fastmath;

		std::unordered_set<Fastmath> out;

		if (flags.noNaNs()) {
			out.insert(Nnan);
		}

		if (flags.noInfs()) {
			out.insert(Ninf);
		}

		if (flags.noSignedZeros()) {
			out.insert(Nsz);
		}

		if (flags.allowReciprocal()) {
			out.insert(Arcp);
		}

		if (flags.allowContract()) {
			out.insert(Contract);
		}

		if (flags.approxFunc()) {
			out.insert(Afn);
		}

		if (flags.allowReassoc()) {
			out.insert(Reassoc);
		}

		if (flags.isFast()) {
			out.insert(Fast);
		}

		return out;
	}

	CConv getCConv(llvm::CallingConv::ID conv) {
		using enum CConv;

		switch (conv) {
			case llvm::CallingConv::C:
				return ccc;
			case llvm::CallingConv::CXX_FAST_TLS:
				return cxx_fast_tlscc;
			case llvm::CallingConv::Fast:
				return fastcc;
			case llvm::CallingConv::GHC:
				return ghccc;
			case llvm::CallingConv::Swift:
				return swiftcc;
			case llvm::CallingConv::PreserveAll:
				return preserve_allcc;
			case llvm::CallingConv::PreserveMost:
				return preserve_mostcc;
			case llvm::CallingConv::X86_VectorCall:
				return x86_vectorcallcc;
			case llvm::CallingConv::ARM_APCS:
				return arm_apcscc;
			case llvm::CallingConv::Cold:
				return coldcc;
			case llvm::CallingConv::PTX_Device:
				return ptx_device;
			case llvm::CallingConv::X86_StdCall:
				return x86_stdcallcc;
			case llvm::CallingConv::AnyReg:
				return anyregcc;
			case llvm::CallingConv::MSP430_INTR:
				return msp430_intrcc;
			case llvm::CallingConv::PTX_Kernel:
				return ptx_kernel;
			case llvm::CallingConv::SPIR_FUNC:
				return spir_func;
			case llvm::CallingConv::Win64:
				return x86_64_win64cc;
			case llvm::CallingConv::ARM_AAPCS_VFP:
				return arm_aapcs_vfpcc;
			case llvm::CallingConv::Intel_OCL_BI:
				return intel_ocl_bicc;
			case llvm::CallingConv::X86_64_SysV:
				return x86_64_sysvcc;
			case llvm::CallingConv::X86_FastCall:
				return x86_fastcallcc;
			case llvm::CallingConv::X86_ThisCall:
				return x86_thiscallcc;
			case llvm::CallingConv::ARM_AAPCS:
				return arm_aapcscc;
			case llvm::CallingConv::SPIR_KERNEL:
				return spir_kernel;
			default:
				throw std::invalid_argument("Invalid calling convention");
		}
	}

	CConv getCConv(std::string_view cconv) {
		using enum CConv;

		if (cconv == "ccc") {
			return ccc;
		}

		if (cconv == "cxx_fast_tlscc") {
			return cxx_fast_tlscc;
		}

		if (cconv == "fastcc") {
			return fastcc;
		}

		if (cconv == "ghccc") {
			return ghccc;
		}

		if (cconv == "swiftcc") {
			return swiftcc;
		}

		if (cconv == "preserve_allcc") {
			return preserve_allcc;
		}

		if (cconv == "preserve_mostcc") {
			return preserve_mostcc;
		}

		if (cconv == "x86_vectorcallcc") {
			return x86_vectorcallcc;
		}

		if (cconv == "arm_apcscc") {
			return arm_apcscc;
		}

		if (cconv == "coldcc") {
			return coldcc;
		}

		if (cconv == "ptx_device") {
			return ptx_device;
		}

		if (cconv == "x86_stdcallcc") {
			return x86_stdcallcc;
		}

		if (cconv == "anyregcc") {
			return anyregcc;
		}

		if (cconv == "msp430_intrcc") {
			return msp430_intrcc;
		}

		if (cconv == "ptx_kernel") {
			return ptx_kernel;
		}

		if (cconv == "spir_func") {
			return spir_func;
		}

		if (cconv == "x86_64_win64cc") {
			return x86_64_win64cc;
		}

		if (cconv == "arm_aapcs_vfpcc") {
			return arm_aapcs_vfpcc;
		}

		if (cconv == "intel_ocl_bicc") {
			return intel_ocl_bicc;
		}

		if (cconv == "x86_64_sysvcc") {
			return x86_64_sysvcc;
		}

		if (cconv == "x86_fastcallcc") {
			return x86_fastcallcc;
		}

		if (cconv == "x86_thiscallcc") {
			return x86_thiscallcc;
		}

		if (cconv == "arm_aapcscc") {
			return arm_aapcscc;
		}

		if (cconv == "spir_kernel") {
			return spir_kernel;
		}

		throw std::invalid_argument("Invalid calling convention");
	}

	RetAttr getRetAttr(llvm::Attribute::AttrKind kind) {
		using enum RetAttr;
		using enum llvm::Attribute::AttrKind;

		switch (kind) {
			case ZExt: return Zeroext;
			case SExt: return Signext;
			case InReg: return Inreg;
			case NoAlias: return Noalias;
			case NonNull: return Nonnull;
			default:
				throw std::invalid_argument("Invalid return attribute");
		}
	}

	Ordering getOrdering(llvm::AtomicOrdering ordering) {
		using enum llvm::AtomicOrdering;

		switch (ordering) {
			case NotAtomic: return Ordering::None;
			case Unordered: return Ordering::Unordered;
			case Monotonic: return Ordering::Monotonic;
			case Acquire: return Ordering::Acquire;
			case Release: return Ordering::Release;
			case AcquireRelease: return Ordering::AcqRel;
			case SequentiallyConsistent: return Ordering::SeqCst;
			default:
				throw std::invalid_argument("Invalid atomic ordering");
		}
	}
}
