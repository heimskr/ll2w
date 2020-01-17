#ifndef PARSER_GLOBALVARDEF_H_
#define PARSER_GLOBALVARDEF_H_

#include "ASTNode.h"
#include "Lexer.h"
#include "Types.h"

namespace LL2W {
	enum class Linkage {
		Default, Private, Appending, AvailableExternally, Weak, Linkonce, ExternWeak, LinkonceOdr, WeakOdr, External,
		Common, Internal
	};
	enum class Visibility {Default, Hidden, Protected};
	enum class DllStorageClass {None, Import, Export};
	enum class ThreadLocal {None, LocalDynamic, InitialExec, LocalExec};
	enum class UnnamedAddr {Default, Unnamed, LocalUnnamed};

	extern std::unordered_map<Linkage, std::string> linkage_map;

	struct GlobalVarDef: public ASTNode {
		Linkage linkage = Linkage::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		ThreadLocal threadLocal = ThreadLocal::None;
		UnnamedAddr unnamedAddr = UnnamedAddr::Default;
		int addrspace = -1;
		bool externallyInitialized = false;
		bool isConstant = false; // Global if false, constant if true
		Type *type;
		// It's assumed that GlobalVarDef is constructed in a parser action. Instead of deleting the initial_value node,
		// we take ownership of it here. It'll be deleted once the GlobalVarDef object is destroyed.
		ASTNode *initialValue;

		using N = ASTNode *;
		GlobalVarDef(N gvar, N linkage_, N visibility_, N dll_storage_class, N thread_local_, N unnamed_addr,
		             N addrspace_, N externally_initialized_, N global_or_constant_, N type_, N initial_value_,
		             N gdef_extras_);

		~GlobalVarDef() { delete type; delete initialValue; }

		std::string debugExtra() override;
	};
}

#endif
