#ifndef PARSER_ENUMS_H_
#define PARSER_ENUMS_H_

#include <string>
#include <unordered_map>

namespace LL2W {
	enum class Linkage {
		Default, Private, Appending, AvailableExternally, Weak, Linkonce, ExternWeak, LinkonceOdr, WeakOdr, External,
		Common, Internal};
	enum class Visibility {Default, Hidden, Protected};
	enum class DllStorageClass {None, Import, Export};
	enum class ThreadLocal {None, LocalDynamic, InitialExec, LocalExec};
	enum class UnnamedAddr {Default, Unnamed, LocalUnnamed};
	enum class CConv {
		Default, ccc, cxx_fast_tlscc, fastcc, ghccc, swiftcc, preserve_allcc, preserve_mostcc, x86_vectorcallcc, cc10,
		cc11, arm_apcscc, coldcc, webkit_jscc, cc64, cc65, cc66, ptx_device, x86_stdcallcc, cc67, cc68, cc69, cc70,
		cc1023, anyregcc, cc71, cc72, cc75, msp430_intrcc, ptx_kernel, cc76, cc77, cc78, spir_func, x86_64_win64cc,
		cc79, cc80, arm_aapcs_vfpcc, intel_ocl_bicc, x86_64_sysvcc, x86_fastcallcc, x86_thiscallcc, arm_aapcscc,
		spir_kernel};
	enum class RetAttr {Zeroext, Signext, Inreg, Noalias, Nonnull};
	enum class ParAttr {Byval, Inalloca, Sret, Nocapture, Readonly};
	enum class Deref {Default, Dereferenceable, DereferenceableOrNull};
	enum class FnAttr {
		alwaysinline, noredzone, convergent, norecurse, inlinehint, inaccessiblemem_or_argmemonly, sspreq,
		sanitize_memory, jumptable, minsize, nobuiltin, noduplicate, noimplicitfloat, builtin, uwtable, nounwind,
		optnone, optsize, readnone, naked, writeonly, argmemonly, returns_twice, safestack, inaccessiblememonly, cold,
		noreturn, nonlazybind, sanitize_thread, thunk, sspstrong, sanitize_address, noinline, ssp, speculatable,
		sanitize_hwaddress, readonly};
	enum class Fastmath {Nnan, Ninf, Nsz, Arcp, Contract, Afn, Reassoc, Fast};
	enum class StructForm {Struct, Class, Union};
	enum class StructShape {Default, Opaque, Packed};

	extern std::unordered_map<Linkage,  std::string> linkage_map;
	extern std::unordered_map<CConv,    std::string> cconv_map;
	extern std::unordered_map<RetAttr,  std::string> retattr_map;
	extern std::unordered_map<ParAttr,  std::string> parattr_map;
	extern std::unordered_map<FnAttr,   std::string> fnattr_map;
	extern std::unordered_map<Fastmath, std::string> fastmath_map;
}

#endif
