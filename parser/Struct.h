#ifndef PARSER_STRUCT_H_
#define PARSER_STRUCT_H_

#include <initializer_list>
#include <vector>

#include "Types.h"

namespace LL2W {
	struct Struct {
		bool opaque;
		std::vector<Type *> types;
		Struct(): opaque(true) {}
		Struct(std::initializer_list<Type *>  types_): opaque(false), types(types_) {}
		Struct(const     std::vector<Type *> &types_): opaque(false), types(types_) {}
	};
}

#endif
