#include "parser/Enums.h"

#include <stdexcept>

// #define USE_SUBSCRIPTS

namespace {
	namespace TypeMap {
		using enum LL2W::TypeType;
		std::unordered_map<LL2W::TypeType, std::string> map{
			{None, "None"}, {Void, "Void"}, {Int, "Int"}, {Array, "Array"}, {Vector, "Vector"}, {Float, "Float"}, {Pointer, "Pointer"}, {Function, "Function"},
			{Struct, "Struct"}, {GlobalTemporary, "GlobalTemporary"}, {Any, "Any"}, {Opaque, "Opaque"},
		};
	}

	namespace ValueMap {
		using enum LL2W::ValueType;
		std::unordered_map<LL2W::ValueType, std::string> map{
			{Double, "Double"}, {Int, "Int"}, {Null, "Null"}, {Vector, "Vector"}, {Bool, "Bool"}, {Local, "Local"}, {Global, "Global"}, {Getelementptr, "Getelementptr"},
			{Void, "Void"}, {Struct, "Struct"}, {Array, "Array"}, {CString, "CString"}, {Undef, "Undef"}, {Zeroinitializer, "Zeroinitializer"}, {Icmp, "Icmp"}, {Logic, "Logic"},
		};
	}

	namespace LinkageMap {
		using enum LL2W::Linkage;
		std::unordered_map<LL2W::Linkage, std::string> map{
			{Private, "private"}, {Appending, "appending"}, {Weak, "weak"}, {Linkonce, "linkonce"}, {ExternWeak, "extern_weak"}, {WeakOdr, "weak_odr"},
			{LinkonceOdr, "linkonce_odr"}, {External, "external"}, {Common, "common"}, {Internal, "internal"}, {AvailableExternally, "available_externally"},
		};
	}

	namespace PreemptionMap {
		using enum LL2W::Preemption;
		std::unordered_map<LL2W::Preemption, std::string> map{
			{Default, "default"}, {DsoPreemptable, "dso_preemptable"}, {DsoLocal, "dso_local"},
		};
	}

	namespace CConvMap {
		using enum LL2W::CConv;
		std::unordered_map<LL2W::CConv, std::string> map{
			{ccc, "ccc"}, {cxx_fast_tlscc, "cxx_fast_tlscc"}, {fastcc, "fastcc"}, {ghccc, "ghccc"}, {swiftcc, "swiftcc"}, {preserve_allcc, "preserve_allcc"},
			{preserve_mostcc, "preserve_mostcc"}, {x86_vectorcallcc, "x86_vectorcallcc"}, {cc10, "cc10"}, {cc11, "cc11"}, {arm_apcscc, "arm_apcscc"},
			{coldcc, "coldcc"}, {webkit_jscc, "webkit_jscc"}, {cc64, "cc64"}, {cc65, "cc65"}, {cc66, "cc66"}, {ptx_device, "ptx_device"},
			{x86_stdcallcc, "x86_stdcallcc"}, {cc67, "cc67"}, {cc68, "cc68"}, {cc69, "cc69"}, {cc70, "cc70"}, {cc1023, "cc1023"}, {anyregcc, "anyregcc"},
			{cc71, "cc71"}, {cc72, "cc72"}, {cc75, "cc75"}, {msp430_intrcc, "msp430_intrcc"}, {ptx_kernel, "ptx_kernel"}, {cc76, "cc76"}, {cc77, "cc77"},
			{cc78, "cc78"}, {spir_func, "spir_func"}, {x86_64_win64cc, "x86_64_win64cc"}, {cc79, "cc79"}, {cc80, "cc80"}, {arm_aapcs_vfpcc, "arm_aapcs_vfpcc"},
			{intel_ocl_bicc, "intel_ocl_bicc"}, {x86_64_sysvcc, "x86_64_sysvcc"}, {x86_fastcallcc, "x86_fastcallcc"}, {x86_thiscallcc, "x86_thiscallcc"},
			{arm_aapcscc, "arm_aapcscc"}, {spir_kernel, "spir_kernel"},
		};
	}

	namespace RetAttrMap {
		using enum LL2W::RetAttr;
		std::unordered_map<LL2W::RetAttr, std::string> map{
			{Zeroext, "zeroext"}, {Signext, "signext"}, {Inreg, "inreg"}, {Noalias, "noalias"}, {Nonnull, "nonnull"}, {Noundef, "noundef"}, {Dereferenceable, "dereferenceable"},
			{Firstint, "firstint"},
		};
	}

	namespace ParAttrMap {
		using enum LL2W::ParAttr;
		std::unordered_map<LL2W::ParAttr, std::string> map{
			{Byval,     "byval"},     {Inalloca,   "inalloca"},   {Sret,     "sret"},    {Nocapture, "nocapture"}, {Readonly, "readonly"},
			{Swiftself, "swiftself"}, {Swifterror, "swifterror"}, {Immarg,   "immarg"},  {Nonnull,   "nonnull"},   {Returned, "returned"},
			{Nest,      "nest"},      {Nofree,     "nofree"},     {Zeroext,  "zeroext"}, {Signext,   "signext"},   {Inreg,    "inreg"},
			{Noalias,   "noalias"},   {Writeonly,  "writeonly"},  {Readnone, "readnone"},
		};
	}

	namespace FnAttrMap {
		using enum LL2W::FnAttr;
		std::unordered_map<LL2W::FnAttr, std::string> map{
			{alwaysinline,     "alwaysinline"},     {noredzone,          "noredzone"},          {convergent,          "convergent"},
			{norecurse,        "norecurse"},        {inlinehint,         "inlinehint"},         {sspreq,              "sspreq"},
			{sanitize_memory,  "sanitize_memory"},  {jumptable,          "jumptable"},          {minsize,             "minsize"},
			{nobuiltin,        "nobuiltin"},        {noduplicate,        "noduplicate"},        {noimplicitfloat,     "noimplicitfloat"},
			{builtin,          "builtin"},          {uwtable,            "uwtable"},            {nounwind,            "nounwind"},
			{optnone,         "optnone"},          {optsize,            "optsize"},            {readnone,            "readnone"},
			{naked,            "naked"},            {writeonly,          "writeonly"},          {argmemonly,          "argmemonly"},
			{returns_twice,    "returns_twice"},    {safestack,          "safestack"},          {inaccessiblememonly, "inaccessiblememonly"},
			{cold,             "cold"},             {noreturn,           "noreturn"},           {nonlazybind,         "nonlazybind"},
			{sanitize_thread,  "sanitize_thread"},  {thunk,              "thunk"},              {sspstrong,           "sspstrong"},
			{sanitize_address, "sanitize_address"}, {noinline,           "noinline"},           {ssp,                 "ssp"},
			{speculatable,     "speculatable"},     {sanitize_hwaddress, "sanitize_hwaddress"}, {readonly,            "readonly"},
			{willreturn,       "willreturn"},       {nosync,             "nosync"},             {inaccessiblemem_or_argmemonly, "inaccessiblemem_or_argmemonly"},
		};
	}

	namespace FastmathMap {
		using enum LL2W::Fastmath;
		std::unordered_map<LL2W::Fastmath, std::string> map{
			{Nnan, "nnan"}, {Ninf, "ninf"}, {Nsz, "nsz"}, {Reassoc, "reassoc"}, {Contract, "contract"}, {Afn, "afn"}, {Arcp, "arcp"}, {Fast, "fast"},
		};
	}

	namespace OrderingMap {
		using enum LL2W::Ordering;
		std::unordered_map<LL2W::Ordering, std::string> map{
			{None, "none"}, {Unordered, "unordered"}, {Monotonic, "monotonic"}, {Acquire, "acquire"}, {Release, "release"}, {AcqRel, "acqrel"}, {SeqCst, "seqcst"},
		};
	}

	namespace ConversionMap {
		using enum LL2W::Conversion;
		std::unordered_map<LL2W::Conversion, std::string> map{
			{None, "none"}, {Trunc, "trunc"}, {Zext, "zext"}, {Sext, "sext"}, {Fptrunc, "fptrunc"}, {Fpext, "fpext"}, {Fptoui, "fptoui"}, {Fptosi, "fptosi"},
			{Uitofp, "uitofp"}, {Sitofp, "sitofp"}, {Ptrtoint, "ptrtoint"}, {Inttoptr, "inttoptr"}, {Bitcast, "bitcast"}, {Addrspacecast, "addrspacecast"},
		};
	}

	namespace QueryTypeMap {
		using enum LL2W::QueryType;
		std::unordered_map<LL2W::QueryType, std::string> map{
			{Memory, "mem"},
		};
	}

	namespace LogicTypeMaps {
		using enum LL2W::LogicType;

		std::unordered_map<LL2W::LogicType, std::string> map{
			{And, "and"}, {Or, "or"}, {Xor, "xor"},
		};

		std::unordered_map<std::string, LL2W::LogicType> inv_map{
			{"and", And}, {"or", Or}, {"xor", Xor},
		};
	}

	namespace TailCallKindMap {
		using enum LL2W::TailCallKind;
		std::unordered_map<LL2W::TailCallKind, std::string> map{
			{None, "none"}, {Tail, "tail"}, {MustTail, "musttail"}, {NoTail, "notail"},
		};
	}

	namespace IcmpCondMaps {
		using enum LL2W::IcmpCond;

#ifdef USE_SUBSCRIPTS
#define U(s) s "ᵤ"
#define S(s) s "ₛ"
#else
#define U(s) s "u"
#define S(s) s "s"
#endif
		std::unordered_map<LL2W::IcmpCond, std::string> map_with_sign {
			{Eq, "=="}, {Ne, "!="},
			{Ugt, U(">")}, {Uge, U(">=")}, {Ult, U("<")}, {Ule, U("<=")},
			{Sgt, S(">")}, {Sge, S(">=")}, {Slt, S("<")}, {Sle, S("<=")},
		};
#undef S
#undef U

		std::unordered_map<std::string, LL2W::IcmpCond> inv_map{
			{"eq", Eq}, {"ne", Ne}, {"ugt", Ugt}, {"uge", Uge}, {"ult", Ult}, {"ule", Ule}, {"sgt", Sgt}, {"sge", Sge}, {"slt", Slt}, {"sle", Sle},
		};

		std::unordered_map<LL2W::IcmpCond, LL2W::IcmpCond> rev_map{
			{Eq, Eq}, {Ne, Ne}, {Ugt, Ult}, {Uge, Ule}, {Ult, Ugt}, {Ule, Uge}, {Sgt, Slt}, {Sge, Sle}, {Slt, Sgt}, {Sle, Sge},
		};

		std::unordered_map<LL2W::IcmpCond, std::string> map{
			{Eq, "eq"}, {Ne, "ne"}, {Ugt, "ugt"}, {Uge, "uge"}, {Ult, "ult"}, {Ule, "ule"}, {Sgt, "sgt"}, {Sge, "sge"}, {Slt, "slt"}, {Sle, "sle"},
		};

		std::unordered_map<LL2W::IcmpCond, std::string> op_map{
			{Eq,  "=="}, {Ne,  "!="},
			{Ugt, ">"},  {Uge, ">="}, {Ult, "<"}, {Ule, "<="},
			{Sgt, ">"},  {Sge, ">="}, {Slt, "<"}, {Sle, "<="},
		};

		std::unordered_set<LL2W::IcmpCond> signed_conds{Sgt, Sge, Sle, Slt};

		std::unordered_set<LL2W::IcmpCond> unsigned_conds{Ugt, Uge, Ule, Ult};
	}
}

namespace LL2W {
	const decltype(TypeMap::map) &type_map = TypeMap::map;
	const decltype(ValueMap::map) &value_map = ValueMap::map;
	const decltype(LinkageMap::map) &linkage_map = LinkageMap::map;
	const decltype(PreemptionMap::map) &preemption_map = PreemptionMap::map;
	const decltype(CConvMap::map) &cconv_map = CConvMap::map;
	const decltype(RetAttrMap::map) &retattr_map = RetAttrMap::map;
	const decltype(ParAttrMap::map) &parattr_map = ParAttrMap::map;
	const decltype(FnAttrMap::map) &fnattr_map = FnAttrMap::map;
	const decltype(FastmathMap::map) &fastmath_map = FastmathMap::map;
	const decltype(OrderingMap::map) &ordering_map = OrderingMap::map;
	const decltype(ConversionMap::map) &conversion_map = ConversionMap::map;
	const decltype(QueryTypeMap::map) &query_map = QueryTypeMap::map;
	const decltype(LogicTypeMaps::map) &logic_map = LogicTypeMaps::map;
	const decltype(LogicTypeMaps::inv_map) &logic_inv_map = LogicTypeMaps::inv_map;
	const decltype(TailCallKindMap::map) &tail_call_kind_map = TailCallKindMap::map;
	const decltype(IcmpCondMaps::inv_map) &cond_inv_map = IcmpCondMaps::inv_map;
	const decltype(IcmpCondMaps::rev_map) &cond_rev_map = IcmpCondMaps::rev_map;
	const decltype(IcmpCondMaps::map) &cond_map = IcmpCondMaps::map;
	const decltype(IcmpCondMaps::op_map) &cond_op_map = IcmpCondMaps::op_map;
	const decltype(IcmpCondMaps::map_with_sign) &cond_op_map_with_sign = IcmpCondMaps::map_with_sign;
	const decltype(IcmpCondMaps::signed_conds) &signed_conds = IcmpCondMaps::signed_conds;
	const decltype(IcmpCondMaps::unsigned_conds) &unsigned_conds = IcmpCondMaps::unsigned_conds;

	bool isSigned(IcmpCond cond) {
		using enum IcmpCond;
		switch (cond) {
			case Sge:
			case Sgt:
			case Slt:
			case Sle:
				return true;
			case Eq:
			case Ne:
			case Uge:
			case Ugt:
			case Ult:
			case Ule:
				return false;
			default:
				throw std::invalid_argument("Invalid IcmpCond in isSigned: " + std::to_string(int(cond)));
		}
	}
}
