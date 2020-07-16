#include "parser/Enums.h"

namespace LL2W {
	std::unordered_map<TypeType, std::string> type_map {
		{TypeType::None,    "None"},    {TypeType::Void,     "Void"},     {TypeType::Int,    "Int"},
		{TypeType::Array,   "Array"},   {TypeType::Vector,   "Vector"},   {TypeType::Float,  "Float"},
		{TypeType::Pointer, "Pointer"}, {TypeType::Function, "Function"}, {TypeType::Struct, "Struct"},
		{TypeType::GlobalTemporary, "GlobalTemporary"}};

	std::unordered_map<ValueType, std::string> value_map {
		{ValueType::Double, "Double"}, {ValueType::Int,             "Int"},           {ValueType::Null,    "Null"},
		{ValueType::Vector, "Vector"}, {ValueType::Bool,            "Bool"},          {ValueType::Local,   "Local"},
		{ValueType::Global, "Global"}, {ValueType::Getelementptr,   "Getelementptr"}, {ValueType::Void,    "Void"},
		{ValueType::Struct, "Struct"}, {ValueType::Array,           "Array"},         {ValueType::CString, "CString"},
		{ValueType::Undef,  "Undef"},  {ValueType::Zeroinitializer, "Zeroinitializer"}};

	std::unordered_map<Linkage, std::string> linkage_map {
		{Linkage::Private,     "private"},      {Linkage::Appending,  "appending"},   {Linkage::Weak,    "weak"},
		{Linkage::Linkonce,    "linkonce"},     {Linkage::ExternWeak, "extern_weak"}, {Linkage::WeakOdr, "weak_odr"},
		{Linkage::LinkonceOdr, "linkonce_odr"}, {Linkage::External,   "external"},    {Linkage::Common,  "common"},
		{Linkage::Internal,    "internal"},     {Linkage::AvailableExternally, "available_externally"}};

	std::unordered_map<CConv, std::string> cconv_map {
		{CConv::Default, "default"}, {CConv::ccc, "ccc"}, {CConv::cxx_fast_tlscc, "cxx_fast_tlscc"},
		{CConv::fastcc, "fastcc"}, {CConv::ghccc, "ghccc"}, {CConv::swiftcc, "swiftcc"},
		{CConv::preserve_allcc, "preserve_allcc"}, {CConv::preserve_mostcc, "preserve_mostcc"},
		{CConv::x86_vectorcallcc, "x86_vectorcallcc"}, {CConv::cc10, "cc10"}, {CConv::cc11, "cc11"},
		{CConv::arm_apcscc, "arm_apcscc"}, {CConv::coldcc, "coldcc"}, {CConv::webkit_jscc, "webkit_jscc"},
		{CConv::cc64, "cc64"}, {CConv::cc65, "cc65"}, {CConv::cc66, "cc66"}, {CConv::ptx_device, "ptx_device"},
		{CConv::x86_stdcallcc, "x86_stdcallcc"}, {CConv::cc67, "cc67"}, {CConv::cc68, "cc68"}, {CConv::cc69, "cc69"},
		{CConv::cc70, "cc70"}, {CConv::cc1023, "cc1023"}, {CConv::anyregcc, "anyregcc"}, {CConv::cc71, "cc71"},
		{CConv::cc72, "cc72"}, {CConv::cc75, "cc75"}, {CConv::msp430_intrcc, "msp430_intrcc"},
		{CConv::ptx_kernel, "ptx_kernel"}, {CConv::cc76, "cc76"}, {CConv::cc77, "cc77"}, {CConv::cc78, "cc78"},
		{CConv::spir_func, "spir_func"}, {CConv::x86_64_win64cc, "x86_64_win64cc"}, {CConv::cc79, "cc79"},
		{CConv::cc80, "cc80"}, {CConv::arm_aapcs_vfpcc, "arm_aapcs_vfpcc"}, {CConv::intel_ocl_bicc, "intel_ocl_bicc"},
		{CConv::x86_64_sysvcc, "x86_64_sysvcc"}, {CConv::x86_fastcallcc, "x86_fastcallcc"},
		{CConv::x86_thiscallcc, "x86_thiscallcc"}, {CConv::arm_aapcscc, "arm_aapcscc"},
		{CConv::spir_kernel, "spir_kernel"}};
	
	std::unordered_map<RetAttr, std::string> retattr_map {
		{RetAttr::Zeroext, "zeroext"}, {RetAttr::Signext, "signext"}, {RetAttr::Inreg, "inreg"},
		{RetAttr::Noalias, "noalias"}, {RetAttr::Nonnull, "nonnull"}};

	std::unordered_map<ParAttr, std::string> parattr_map {
		{ParAttr::Byval,      "byval"},      {ParAttr::Inalloca, "inalloca"}, {ParAttr::Sret,      "sret"},
		{ParAttr::Nocapture,  "nocapture"},  {ParAttr::Readonly, "readonly"}, {ParAttr::Swiftself, "swiftself"},
		{ParAttr::Swifterror, "swifterror"}, {ParAttr::Immarg,   "immarg"},   {ParAttr::Nonnull,   "nonnull"},
		{ParAttr::Returned,   "returned"},   {ParAttr::Nest,     "nest"},     {ParAttr::Nofree,    "nofree"},
		{ParAttr::Zeroext,    "zeroext"},    {ParAttr::Signext,  "signext"},  {ParAttr::Inreg,     "inreg"},
		{ParAttr::Noalias,    "noalias"}};

	std::unordered_map<FnAttr, std::string> fnattr_map {
		{FnAttr::alwaysinline,       "alwaysinline"},       {FnAttr::noredzone,           "noredzone"},
		{FnAttr::convergent,         "convergent"},         {FnAttr::norecurse,           "norecurse"},
		{FnAttr::inlinehint,         "inlinehint"},         {FnAttr::sspreq,              "sspreq"},
		{FnAttr::sanitize_memory,    "sanitize_memory"},    {FnAttr::jumptable,           "jumptable"},
		{FnAttr::minsize,            "minsize"},            {FnAttr::nobuiltin,           "nobuiltin"},
		{FnAttr::noduplicate,        "noduplicate"},        {FnAttr::noimplicitfloat,     "noimplicitfloat"},
		{FnAttr::builtin,            "builtin"},            {FnAttr::uwtable,             "uwtable"},
		{FnAttr::nounwind,           "nounwind"},           {FnAttr::optnone,             "optnone"},
		{FnAttr::optsize,            "optsize"},            {FnAttr::readnone,            "readnone"},
		{FnAttr::naked,              "naked"},              {FnAttr::writeonly,           "writeonly"},
		{FnAttr::argmemonly,         "argmemonly"},         {FnAttr::returns_twice,       "returns_twice"},
		{FnAttr::safestack,          "safestack"},          {FnAttr::inaccessiblememonly, "inaccessiblememonly"},
		{FnAttr::cold,               "cold"},               {FnAttr::noreturn,            "noreturn"},
		{FnAttr::nonlazybind,        "nonlazybind"},        {FnAttr::sanitize_thread,     "sanitize_thread"},
		{FnAttr::thunk,              "thunk"},              {FnAttr::sspstrong,           "sspstrong"},
		{FnAttr::sanitize_address,   "sanitize_address"},   {FnAttr::noinline,            "noinline"},
		{FnAttr::ssp,                "ssp"},                {FnAttr::speculatable,        "speculatable"},
		{FnAttr::sanitize_hwaddress, "sanitize_hwaddress"}, {FnAttr::readonly,            "readonly"},
		{FnAttr::inaccessiblemem_or_argmemonly, "inaccessiblemem_or_argmemonly"}};

	std::unordered_map<Fastmath, std::string> fastmath_map {
		{Fastmath::Nnan,    "nnan"},    {Fastmath::Ninf,     "ninf"},     {Fastmath::Nsz, "nsz"},
		{Fastmath::Reassoc, "reassoc"}, {Fastmath::Contract, "contract"}, {Fastmath::Afn, "afn"},
		{Fastmath::Arcp,    "arcp"},    {Fastmath::Fast,     "fast"}};

	std::unordered_map<Ordering, std::string> ordering_map {
		{Ordering::None,    "none"},    {Ordering::Unordered, "unordered"}, {Ordering::Monotonic, "monotonic"},
		{Ordering::Acquire, "acquire"}, {Ordering::Release,   "release"},   {Ordering::AcqRel,    "acqrel"},
		{Ordering::SeqCst, "seqcst"}};

	std::unordered_map<IcmpCond, std::string> cond_map {
		{IcmpCond::Eq,  "eq"},  {IcmpCond::Ne,  "ne"},  {IcmpCond::Ugt, "ugt"}, {IcmpCond::Uge, "uge"},
		{IcmpCond::Ult, "ult"}, {IcmpCond::Ule, "ule"}, {IcmpCond::Sgt, "sgt"}, {IcmpCond::Sge, "sge"},
		{IcmpCond::Slt, "slt"}, {IcmpCond::Sle, "sle"}};

	std::unordered_map<IcmpCond, std::string> cond_op_map {
		{IcmpCond::Eq,  "=="}, {IcmpCond::Ne,  "!="},
		{IcmpCond::Ugt, ">"},  {IcmpCond::Uge, ">="}, {IcmpCond::Ult, "<"}, {IcmpCond::Ule, "<="},
		{IcmpCond::Sgt, ">"},  {IcmpCond::Sge, ">="}, {IcmpCond::Slt, "<"}, {IcmpCond::Sle, "<="}};

	std::unordered_map<IcmpCond, IcmpCond> cond_rev_map {
		{IcmpCond::Eq, IcmpCond::Eq}, {IcmpCond::Ne, IcmpCond::Ne}, {IcmpCond::Ugt, IcmpCond::Ult},
		{IcmpCond::Uge, IcmpCond::Ule}, {IcmpCond::Ult, IcmpCond::Ugt}, {IcmpCond::Ule, IcmpCond::Uge},
		{IcmpCond::Sgt, IcmpCond::Slt}, {IcmpCond::Sge, IcmpCond::Sle}, {IcmpCond::Slt, IcmpCond::Sgt},
		{IcmpCond::Sle, IcmpCond::Sge}};

	std::unordered_map<Conversion, std::string> conversion_map {
		{Conversion::None,    "none"},    {Conversion::Trunc,    "trunc"},    {Conversion::Zext,     "zext"},
		{Conversion::Sext,    "sext"},    {Conversion::Fptrunc,  "fptrunc"},  {Conversion::Fpext,    "fpext"},
		{Conversion::Fptoui,  "fptoui"},  {Conversion::Fptosi,   "fptosi"},   {Conversion::Uitofp,   "uitofp"},
		{Conversion::Sitofp,  "sitofp"},  {Conversion::Ptrtoint, "ptrtoint"}, {Conversion::Inttoptr, "inttoptr"},
		{Conversion::Bitcast, "bitcast"}, {Conversion::Addrspacecast, "addrspacecast"}};
}
