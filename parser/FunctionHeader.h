#ifndef PARSER_FUNCTIONHEADER_H_
#define PARSER_FUNCTIONHEADER_H_

#include <unordered_set>

#include "GlobalVarDef.h"

namespace LL2W {
	enum class CConv {
		Default, ccc, cxx_fast_tlscc, fastcc, ghccc, swiftcc, preserve_allcc, preserve_mostcc, x86_vectorcallcc, cc10,
		cc11, arm_apcscc, coldcc, webkit_jscc, cc64, cc65, cc66, ptx_device, x86_stdcallcc, cc67, cc68, cc69, cc70,
		cc1023, anyregcc, cc71, cc72, cc75, msp430_intrcc, ptx_kernel, cc76, cc77, cc78, spir_func, x86_64_win64cc,
		cc79, cc80, arm_aapcs_vfpcc, intel_ocl_bicc, x86_64_sysvcc, x86_fastcallcc, x86_thiscallcc, arm_aapcscc,
		spir_kernel
	};

	enum class RetAttr {Zeroext, Signext, Inreg, Noalias, Nonnull};

	enum class Deref {Default, Dereferenceable, DereferenceableOrNull};

	extern std::unordered_map<CConv, std::string> cconv_map;
	extern std::unordered_map<RetAttr, std::string> retattr_map;

	struct FunctionHeader: public ASTNode {
		const std::string *name;
		Linkage linkage = Linkage::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		CConv cconv = CConv::Default;
		Deref deref = Deref::Default;
		std::unordered_set<RetAttr> retattrs;
		int dereferenceableBytes = -1; // TODO: separate values for dereferenceable and dereferenceable_or_null?
		Type *returnType;
		std::vector<Type *> argumentTypes;
		
		using N = ASTNode *;
		FunctionHeader(N linkage_, N visibility_, N dll_storage_class, N cconv_, N retattrs_, N type, N function_name,
		               N function_args, N unnamed_addr, N fnattrs_);
		~FunctionHeader() { delete returnType; }

		std::string debugExtra() override;
	};

	struct FunctionArgs: public ASTNode {
		bool ellipse;
		FunctionArgs(ASTNode *list, bool ellipse_): ASTNode(FUNCTION_ARGS, ""), ellipse(ellipse_) { absorb(list); }
	};

	struct FunctionArgument {
		Type *type;
	};
}

#endif
