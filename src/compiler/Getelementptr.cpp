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

		const long front = indices.front();
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
#ifdef STRUCT_PAD_CUSTOM
				std::cerr << "Custom: " << stype->barename() << "\n";
				for (long i = 0; i < front; ++i) {
					const long width = Util::alignToPower(snode->types.at(i)->width());
					offset = Util::upalign(offset, width);
					std::cerr << i << ": offset=" << (offset / 8) << " (" << offset << "), width=" << width << "\n";
					if (i != front - 1)
						offset += width;
				}
				std::cerr << "Final: " << (offset / 8) << " (" << offset << ")\n";
#elif defined(STRUCT_PAD_X86)
				std::cerr << "x86: " << stype->barename() << "\n";
				for (long i = 0; i < front; ++i) {
					const long width = snode->types.at(i)->width();
					offset = Util::upalign(offset, width) + width;
					std::cerr << i << ": offset=" << offset << "\n";
				}
#else
				for (long i = 0; i < front; ++i)
					offset += snode->types.at(i)->width();
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