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

	class Parser;

	class ASTNode {
		private:
			ASTNode() {}

		public:
			Parser *parser;
			int symbol;
			Location location;
			const std::string *lexerInfo;
			ASTNode *parent = nullptr;
			std::list<ASTNode *> children;

			ASTNode(Parser &, int sym, const Location &loc, const char *info);
			ASTNode(Parser &, int sym, const Location &loc, const std::string *info);
			ASTNode(Parser &, int sym, const char *info);
			ASTNode(Parser &, int sym, const std::string *info);
			ASTNode(Parser &, int sym, const Location &loc);
			ASTNode(Parser &, int sym);
			/** Constructs an ASTNode that adopts another node and copies its location. */
			ASTNode(Parser &, int sym, ASTNode *, const char *info = "");
			ASTNode(Parser &, int sym, ASTNode *, const std::string *info);
			virtual ~ASTNode();

			ASTNode * operator[](size_t) const;
			ASTNode * at(size_t) const;
			size_t size() const;
			bool empty() const;
			ASTNode * adopt(ASTNode *, bool do_locate = false);
			ASTNode * adopt(std::initializer_list<ASTNode *>);
			ASTNode * absorb(ASTNode *);
			ASTNode * clear();
			ASTNode * copy() const;
			/** Copies the location from another node. */
			ASTNode * locate(const ASTNode *);
			/** Copies the location from the first node in the list that isn't null. */
			ASTNode * locate(std::initializer_list<const ASTNode *>);
			ASTNode * locate(const Location &);
			/** Concatenates the lexerInfo fields of every element of the children vector. */
			std::string concatenate() const;
			long atoi() const;
			long atoi(int offset) const;
			bool isType() const;
			bool isValue() const;
			const char * getName() const;
			void debug(int indent = 0, bool is_last = false, bool suppress_line = false) const;
			virtual std::string debugExtra() const;
			virtual std::string style() const;

			static void destroy(std::initializer_list<ASTNode *>);

			ASTNode * front() const;
			ASTNode * back() const;
			decltype(children)::iterator begin();
			decltype(children)::iterator end();
			decltype(children)::const_iterator begin() const;
			decltype(children)::const_iterator end() const;
			decltype(children)::const_iterator cbegin() const noexcept;
			decltype(children)::const_iterator cend() const noexcept;

			std::string extractName() const;
			const std::string * extracted() const;
	};
}

#endif
