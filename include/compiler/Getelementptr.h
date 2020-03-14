#ifndef COMPILER_GETELEMENTPTR_H_
#define COMPILER_GETELEMENTPTR_H_

#include <list>
#include <memory>

namespace LL2W::Getelementptr {
	class Type;

	int compute(std::shared_ptr<Type>, std::list<int>);
}

#endif
