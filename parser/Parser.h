#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <string>

#include <stdio.h>

#include "ASTNode.h"

namespace LL2W {
	class Parser {
		private:
			static std::string filename;

		public:
			static ASTNode *root;
			Parser() = delete;
			static void open(const std::string &filename);
			static void parse();
			static void done();

			static const char * getName(int symbol);
	};
}

#endif
