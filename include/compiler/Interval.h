#ifndef COMPILER_INTERVAL_H_
#define COMPILER_INTERVAL_H_

#include <memory>

namespace LL2W {
	class BasicBlock;
	class Variable;

	struct Interval {
		std::shared_ptr<BasicBlock> firstDefinition, lastUse;
		Variable *variable = nullptr;
		int reg = -1;

		Interval(Variable &);
	};
}

#endif
