#include <iostream>

#include "compiler/Getelementptr.h"
#include "exception/TypeError.h"
#include "parser/Types.h"
#include "parser/StructNode.h"
#include "parser/Values.h"

namespace LL2W::Getelementptr {
	int compute_mutating(TypePtr type, std::list<int> &indices, TypePtr *out_type, bool first = true) {
		if (indices.empty()) {
			if (out_type)
				*out_type = std::make_shared<PointerType>(type->copy());
			return 0;
		}

		int front = indices.front();
		indices.pop_front();
		switch (type->typeType()) {
			case TypeType::Pointer: {
				TypePtr subtype = dynamic_cast<PointerType *>(type.get())->subtype;
				return front * subtype->width() + compute_mutating(subtype, indices, out_type, false);
			}
			case TypeType::Array: {
				TypePtr subtype = dynamic_cast<ArrayType *>(type.get())->subtype;
				return front * subtype->width() + compute_mutating(subtype, indices, out_type, false);
			}
			case TypeType::Struct: {
				std::shared_ptr<StructType> stype = std::dynamic_pointer_cast<StructType>(type);
				std::shared_ptr<StructNode> snode = stype->node;
				if (!snode) {
					stype = StructType::knownStructs.at(stype->barename());
					snode = stype->node;
				}

				int offset = 0;
#ifndef STRUCT_PAD_X86
				for (int i = 0; i < front; ++i)
					offset += snode->types.at(i)->width();
#else
				int width;
				for (int i = 0; i < front; ++i) {
					width = snode->types.at(i)->width();
					offset += width + ((width - (offset % width)) % width);
				}
#endif
				return offset + compute_mutating(snode->types.at(front), indices, out_type, false);
			}
			default: throw TypeError("Getelementptr::compute encountered an invalid type", type);
		}
	}

	int compute(TypePtr type, std::list<int> indices, TypePtr *out_type) {
		return compute_mutating(type, indices, out_type);
	}

	int compute(const GetelementptrValue *value, TypePtr *out_type) {
		std::list<int> indices;
		for (const std::pair<int, long> &decimal_pair: value->decimals)
			indices.push_back(decimal_pair.second);
		return compute_mutating(value->ptrType, indices, out_type);
	}
}