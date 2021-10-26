#include <iostream>

#include "compiler/Getelementptr.h"
#include "exception/TypeError.h"
#include "parser/Types.h"
#include "parser/StructNode.h"
#include "parser/Values.h"

namespace LL2W::Getelementptr {
	long compute_mutating(TypePtr type, std::list<long> &indices, TypePtr *out_type) {
		if (indices.empty()) {
			if (out_type)
				*out_type = std::make_shared<PointerType>(type->copy());
			return 0;
		}

		auto front = indices.front();
		indices.pop_front();
		switch (type->typeType()) {
			case TypeType::Pointer:
			case TypeType::Array: {
				TypePtr subtype = dynamic_cast<HasSubtype *>(type.get())->subtype;
				return front * subtype->width() + compute_mutating(subtype, indices, out_type);
			}
			case TypeType::Struct: {
				std::shared_ptr<StructType> stype = std::dynamic_pointer_cast<StructType>(type);
				std::shared_ptr<StructNode> snode = stype->node;
				if (!snode) {
					stype = StructType::knownStructs.at(stype->barename());
					snode = stype->node;
				}

				long offset = 0;
#ifndef STRUCT_PAD_X86
				for (long i = 0; i < front; ++i)
					offset += snode->types.at(i)->width();
#else
				long width;
				for (long i = 0; i < front; ++i) {
					width = snode->types.at(i)->width();
					offset += width + ((width - (offset % width)) % width);
				}
#endif
				return offset + compute_mutating(snode->types.at(front), indices, out_type);
			}
			default: throw TypeError("Getelementptr::compute encountered an invalid type", type);
		}
	}

	long compute(TypePtr type, std::list<long> indices, TypePtr *out_type) {
		return compute_mutating(type, indices, out_type);
	}

	long compute(const GetelementptrValue *value, TypePtr *out_type) {
		std::list<long> indices = Getelementptr::getIndices(*value);
		return compute_mutating(value->ptrType, indices, out_type);
	}

	std::list<long> getIndices(const GetelementptrValue &value) {
		std::list<long> indices;
		for (const auto &decimal_pair: value.decimals)
			if (!std::holds_alternative<long>(decimal_pair.second)) {
				warn() << "GetelementptrValue decimal's second item is a pvar. Incorrect code will be produced.\n";
				indices.push_back(0);
			} else
				indices.push_back(std::get<long>(decimal_pair.second));
		return indices;
	}
}