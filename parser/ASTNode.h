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
		void debug(int indent = 0);
		virtual std::string debugExtra();

		static void destroy(std::initializer_list<ASTNode *>);
	};

	struct MetadataDef: public ASTNode {
		bool distinct;
		MetadataDef(ASTNode *decvar, ASTNode *distinct, ASTNode *list);
		std::string debugExtra() override;
	};


}

#endif
