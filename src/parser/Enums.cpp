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
			{Eq, Eq}, {Ne, Ne}, {Ugt, Ult}, {Uge, Ule}, {Ult, Ugt}, {Ule, Uge}, {Sgt, Slt}, {Sge, Sle}, {Slt, Sgt}, {Sle, Sge}, {Xge, Xle}, {Xgt, Xlt}, {Xlt, Xgt}, {Xle, Xge},
		};

		std::unordered_map<LL2W::IcmpCond, std::string> map{
			{Eq, "eq"}, {Ne, "ne"}, {Ugt, "ugt"}, {Uge, "uge"}, {Ult, "ult"}, {Ule, "ule"}, {Sgt, "sgt"}, {Sge, "sge"}, {Slt, "slt"}, {Sle, "sle"},
		};

		std::unordered_map<LL2W::IcmpCond, std::string> op_map{
			{Eq,  "=="}, {Ne,  "!="},
			{Ugt, ">"},  {Uge, ">="}, {Ult, "<"}, {Ule, "<="},
			{Sgt, ">"},  {Sge, ">="}, {Slt, "<"}, {Sle, "<="},
			{Xgt, ">"},  {Xge, ">="}, {Xlt, "<"}, {Xle, "<="},
		};

		std::unordered_set<LL2W::IcmpCond> signed_conds{Sgt, Sge, Sle, Slt};

		std::unordered_set<LL2W::IcmpCond> unsigned_conds{Ugt, Uge, Ule, Ult};
	}
}

namespace LL2W {
	const auto &type_map = TypeMap::map;
	const auto &value_map = ValueMap::map;
	const auto &linkage_map = LinkageMap::map;
	const auto &preemption_map = PreemptionMap::map;
	const auto &cconv_map = CConvMap::map;
	const auto &retattr_map = RetAttrMap::map;
	const auto &parattr_map = ParAttrMap::map;
	const auto &fnattr_map = FnAttrMap::map;
	const auto &fastmath_map = FastmathMap::map;
	const auto &ordering_map = OrderingMap::map;
	const auto &conversion_map = ConversionMap::map;
	const auto &query_map = QueryTypeMap::map;
	const auto &logic_map = LogicTypeMaps::map;
	const auto &logic_inv_map = LogicTypeMaps::inv_map;
	const auto &tail_call_kind_map = TailCallKindMap::map;
	const auto &cond_inv_map = IcmpCondMaps::inv_map;
	const auto &cond_rev_map = IcmpCondMaps::rev_map;
	const auto &cond_map = IcmpCondMaps::map;
	const auto &cond_op_map = IcmpCondMaps::op_map;
	const auto &cond_op_map_with_sign = IcmpCondMaps::map_with_sign;
	const auto &signed_conds = IcmpCondMaps::signed_conds;
	const auto &unsigned_conds = IcmpCondMaps::unsigned_conds;

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
