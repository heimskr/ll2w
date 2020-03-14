#include "compiler/Getelementptr.h"
#include "exception/TypeError.h"
#include "parser/Types.h"

namespace LL2W::Getelementptr {
	int compute_mutating(TypePtr type, std::list<int> &indices) {
		if (indices.empty())
			return 0;

		int front = indices.front();
		indices.pop_front();
		switch (type->typeType()) {
			case TypeType::Pointer: {
				TypePtr subtype = std::dynamic_pointer_cast<PointerType>(type)->subtype;
				return front * subtype->width() + compute_mutating(subtype, indices);
			}
			default: throw TypeError("Getelementptr::compute encountered an invalid type", type);
		}
	}

	int compute(TypePtr type, std::list<int> indices) {
		return compute_mutating(type, indices);
	}
}