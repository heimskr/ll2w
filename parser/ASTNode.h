#ifndef PARSER_ASTNODE_H_
#define PARSER_ASTNODE_H_

#include <initializer_list>
#include <ostream>
#include <string>
#include <vector>

namespace LL2W {
	struct Location {
		int fileno;
		size_t line;
		size_t column;

		operator std::string() const;
		const std::string * filename() const;
	};

	std::ostream & operator<<(std::ostream &, const Location &);

	struct ASTNode {
		int symbol;
		Location location;
		const std::string *lexerInfo;
		ASTNode *parent;
		std::vector<ASTNode *> children;

		ASTNode(int sym, const Location &loc, const char *info);
		ASTNode(int sym, const Location &loc, const std::string *info);
		ASTNode(int sym, const char *info);
		ASTNode(int sym, const std::string *info);
		virtual ~ASTNode();

		ASTNode * adopt(ASTNode *);
		ASTNode * adopt(std::initializer_list<ASTNode *>);
		ASTNode * absorb(ASTNode *);
		ASTNode * clear();
		/** Concatenates the lexerInfo fields of every element of the children vector. */
		std::string concatenate() const;
		void debug(int indent = 0, bool is_last = false);
		virtual std::string debugExtra();

		static void destroy(std::initializer_list<ASTNode *>);
	};

	struct MetadataDef: public ASTNode {
		bool distinct;
		MetadataDef(ASTNode *decvar, ASTNode *distinct, ASTNode *list);
		std::string debugExtra() override;
	};


	enum class Linkage {
		Default, Private, Appending, AvailableExternally, Weak, Linkonce, ExternWeak, LinkonceOdr, WeakOdr, External,
		Common, Internal
	};
	enum class Visibility {Default, Hidden, Protected};
	enum class DllStorageClass {None, Import, Export};
	enum class ThreadLocal {None, LocalDynamic, InitialExec, LocalExec};

	struct GlobalVarDef: public ASTNode {
		Linkage linkage = Linkage::Default;
		Visibility visibility = Visibility::Default;
		DllStorageClass dllStorageClass = DllStorageClass::None;
		ThreadLocal threadLocal = ThreadLocal::None;

		GlobalVarDef(ASTNode *gvar_, ASTNode *linkage_, ASTNode *visibility_, ASTNode *dll_storage_class_,
		             ASTNode *thread_local_, ASTNode *unnamed_addr_, ASTNode *addrspace_,
		             ASTNode *externally_initialized_, ASTNode *global_or_constant_, ASTNode *type_,
		             ASTNode *initial_value_, ASTNode *gdef_extras_);

		std::string debugExtra() override;
	};
}

#endif
