#pragma once

#include <memory>
#include <unordered_set>

#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "ParAttrs.h"
#include "util/Makeable.h"

namespace LL2W {
	class ASTNode;

	struct Constant;
	using ConstantPtr = std::shared_ptr<Constant>;

	struct Constant: Makeable<Constant> {
		TypePtr type;
		ValuePtr value;
		ParAttrs parattrs;
		Conversion conversion = Conversion::None;
		ConstantPtr conversionSource = nullptr;
		TypePtr conversionType = nullptr;

		Constant() = delete;
		Constant(const Constant &) = delete;
		Constant(TypePtr, ValuePtr, const ParAttrs &, Conversion, ConstantPtr, TypePtr);
		Constant(const ASTNode *, TypePtr type_hint = nullptr);

		ConstantPtr copy() const;
		/** Applies ptrtoint/inttoptr conversions and returns a new Constant. */
		ConstantPtr convert() const;
		operator std::string() const;
	};

	std::ostream & operator<<(std::ostream &, const Constant &);
}
