#pragma once

#include <memory>
#include <unordered_set>

#include "Enums.h"

namespace LL2W {
	class ASTNode;
	class Type;

	/** Represents a set of parameter attributes. */
	struct ParAttrs {
		std::unordered_set<ParAttr> attributes;
		std::shared_ptr<Type> byvalType = nullptr;
		int align = -1, dereferenceable = -1;
		bool orNull = false;
		bool signext = false;

		ParAttrs();
		ParAttrs(const ASTNode &);
		ParAttrs(const ParAttrs &);

		ParAttrs & operator=(const ParAttrs &);

		operator std::string() const;
	};
}
