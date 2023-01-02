#pragma once

#include <memory>
#include <string>

namespace LL2W {
	class Instruction;
	struct BrUncondNode;
	struct BrCondNode;
	struct RetNode;
	struct SwitchNode;
	struct UnreachableNode;

	namespace CompilerUtil {
		bool labelsMatch(std::string_view, std::string_view);

		   BrUncondNode *    brUncondCast(const std::shared_ptr<Instruction> &);
		     BrCondNode *      brCondCast(const std::shared_ptr<Instruction> &);
		        RetNode *         retCast(const std::shared_ptr<Instruction> &);
		     SwitchNode *      switchCast(const std::shared_ptr<Instruction> &);
		UnreachableNode * unreachableCast(const std::shared_ptr<Instruction> &);
	}
}
