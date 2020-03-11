#ifndef UTIL_COMPILERUTIL_H_
#define UTIL_COMPILERUTIL_H_

#include <memory>

namespace LL2W {
	class Instruction;
	struct BrUncondNode;
	struct BrCondNode;
	struct RetNode;
	struct UnreachableNode;

	namespace CompilerUtil {
		bool isTerminator(std::shared_ptr<Instruction>);

		   BrUncondNode *    brUncondCast(std::shared_ptr<Instruction>);
		     BrCondNode *      brCondCast(std::shared_ptr<Instruction>);
		        RetNode *         retCast(std::shared_ptr<Instruction>);
		UnreachableNode * unreachableCast(std::shared_ptr<Instruction>);
	}
}

#endif
