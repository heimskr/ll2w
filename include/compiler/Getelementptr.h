#ifndef COMPILER_GETELEMENTPTR_H_
#define COMPILER_GETELEMENTPTR_H_

#include <list>
#include <memory>

namespace LL2W {
	class Type;
	struct GetelementptrValue;

	namespace Getelementptr {
		/** Computes the offset (in bits) of a getelementptr expression. */
		long compute(std::shared_ptr<Type>, std::list<long>, std::shared_ptr<Type> *out_type = nullptr);

		/** Computes the offset (in bits) of a getelementptr expression. */
		long compute(const GetelementptrValue *, std::shared_ptr<Type> *out_type = nullptr);

		/** Returns a list of indices from a GetelementptrValue, checking to see whether all of them are longs. For each
		 *  pvar in the decimals, a warning will be printed and 0 will be added to the list. */
		std::list<long> getIndices(const GetelementptrValue &);
	}
}

#endif
