#pragma once

#include <initializer_list>
#include <iostream>
#include <list>
#include <ostream>
#include <set>
#include <sstream>
#include <string>

// #define TRACK_ASTNODES

namespace LL2W {
	struct ASTLocation {
		size_t line;
		size_t column;

		operator std::string() const;
	};

	std::ostream & operator<<(std::ostream &, const ASTLocation &);

	class Parser;

	class ASTNode {
		private:
			static void onCreate(ASTNode *);
			static void onDestroy(ASTNode *);
			void recursiveStringify(std::stringstream &) const;

		public:
			Parser *parser;
			int symbol;
			ASTLocation location;
			const std::string *lexerInfo;
			ASTNode *parent = nullptr;
			std::list<ASTNode *> children;
			int debugIndex = -1;

			ASTNode() = default;
			ASTNode(Parser &, int sym, const ASTLocation &loc, const char *info);
			ASTNode(Parser &, int sym, const ASTLocation &loc, const std::string *info);
			ASTNode(Parser &, int sym, const char *info);
			ASTNode(Parser &, int sym, const std::string *info);
			ASTNode(Parser &, int sym, const ASTLocation &loc);
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
			ASTNode * locate(const ASTLocation &);
			ASTNode * setDebug(int);
			/** Copies the debug index from and deletes the given "!dbg" node. */
			ASTNode * setDebug(ASTNode *);
			/** Concatenates the lexerInfo fields of every element of the children vector. */
			std::string concatenate() const;
			int64_t atoi() const;
			int64_t atoi(size_t offset) const;
			std::string unquote() const;
			bool isType() const;
			bool isValue() const;
			const char * getName() const;
			void debug(int indent = 0, bool is_last = false, bool suppress_line = false) const;
			virtual std::string debugExtra() const;
			virtual std::string style() const;
			std::string recursiveStringify() const;

			static void destroy(std::initializer_list<ASTNode *>);

			ASTNode * front() const;
			ASTNode * back() const;
			decltype(children)::iterator begin();
			decltype(children)::iterator end();
			decltype(children)::const_iterator begin() const;
			decltype(children)::const_iterator end() const;
			decltype(children)::reverse_iterator rbegin();
			decltype(children)::reverse_iterator rend();
			decltype(children)::const_reverse_iterator rbegin() const;
			decltype(children)::const_reverse_iterator rend() const;
			decltype(children)::const_iterator cbegin() const noexcept;
			decltype(children)::const_iterator cend() const noexcept;
			decltype(children)::const_reverse_iterator crbegin() const noexcept;
			decltype(children)::const_reverse_iterator crend() const noexcept;

			std::string extractName() const;
			const std::string * extracted() const;
	};
}

#ifdef TRACK_ASTNODES
extern std::set<LL2W::ASTNode *> all_nodes;
#endif
