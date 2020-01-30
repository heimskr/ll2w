#include "parser/ASTNode.h"
#include "compiler/BasicBlock.h"
#include "compiler/Program.h"

namespace LL2W {
	Program::Program(const ASTNode &root) {
		for (const ASTNode *node: root) {
			switch (node->symbol) {
				case FUNCTION_DEF:
					// functions.insert({*node->lexerInfo, 
					functions.emplace(*node->lexerInfo, std::move(Function(*node)));
					break;
				default: ;
			}
		}
	}	
}