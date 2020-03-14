#ifndef COMPILER_GETELEMENTPTR_H_
#define COMPILER_GETELEMENTPTR_H_

#include <list>
#include <memory>

namespace LL2W {
	class Type;

	namespace Getelementptr {
		/** Computes the offset (in bits) of a getelementptr expression. */
		int compute(std::shared_ptr<Type>, std::list<int>);
	}
}

#endif
