#include <iostream>

#include "compiler/Getelementptr.h"
#include "exception/TypeError.h"
#include "parser/Types.h"
#include "parser/StructNode.h"

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
			case TypeType::Array: {
				TypePtr subtype = std::dynamic_pointer_cast<ArrayType>(type)->subtype;
				return front * subtype->width() + compute_mutating(subtype, indices);
			}
			case TypeType::Struct: {
				std::shared_ptr<StructType> stype = std::dynamic_pointer_cast<StructType>(type);
				std::shared_ptr<StructNode> snode = stype->node;
				if (!snode) {
					stype = StructType::knownStructs.at(stype->barename());
					snode = stype->node;
				}

				int offset = 0;
				for (int i = 0; i < front; ++i) {
					offset += snode->types.at(i)->width();
				}
				return offset + compute_mutating(snode->types.at(front), indices);
			}
			default: throw TypeError("Getelementptr::compute encountered an invalid type", type);
		}
	}

	int compute(TypePtr type, std::list<int> indices) {
		return compute_mutating(type, indices);
	}
}