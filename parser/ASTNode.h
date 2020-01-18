#ifndef PARSER_ASTNODE_H_
#define PARSER_ASTNODE_H_

#include <initializer_list>
#include <list>
#include <ostream>
#include <string>

namespace LL2W {
	struct Location {
		size_t line;
		size_t column;

		operator std::string() const;
	};

	std::ostream & operator<<(std::ostream &, const Location &);

	class ASTNode {
		private:
			ASTNode() {}

		public:
			int symbol;
			Location location;
			const std::string *lexerInfo;
			ASTNode *parent;
			std::list<ASTNode *> children;

			ASTNode(int sym, const Location &loc, const char *info);
			ASTNode(int sym, const Location &loc, const std::string *info);
			ASTNode(int sym, const char *info);
			ASTNode(int sym, const std::string *info);
			virtual ~ASTNode();

			ASTNode * operator[](size_t) const;
			ASTNode * at(size_t) const;
			size_t size() const;
			ASTNode * adopt(ASTNode *);
			ASTNode * adopt(std::initializer_list<ASTNode *>);
			ASTNode * absorb(ASTNode *);
			ASTNode * clear();
			ASTNode * copy() const;
			/** Concatenates the lexerInfo fields of every element of the children vector. */
			std::string concatenate() const;
			void debug(int indent = 0, bool is_last = false);
			virtual std::string debugExtra();
			virtual std::string style() const;

			static void destroy(std::initializer_list<ASTNode *>);

			std::string extractName() const;
	};

	struct MetadataDef: public ASTNode {
		bool distinct;
		MetadataDef(ASTNode *decvar, ASTNode *distinct, ASTNode *list);
		std::string debugExtra() override;
	};
}

#endif
