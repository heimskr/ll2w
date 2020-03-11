#ifndef UTIL_COMPILERUTIL_H_
#define UTIL_COMPILERUTIL_H_

#include <memory>

namespace LL2W {
	struct BrUncondNode;
	struct BrCondNode;
	class Instruction;

	namespace CompilerUtil {
		BrUncondNode * brUncondCast(std::shared_ptr<Instruction>);
		BrCondNode * brCondCast(std::shared_ptr<Instruction>);
	}
}

#endif
