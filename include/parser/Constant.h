#ifndef PARSER_CONSTANT_H_
#define PARSER_CONSTANT_H_

#include <memory>
#include <unordered_set>

#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "ParAttrs.h"

namespace LL2W {
	class ASTNode;

	struct Constant;
	using ConstantPtr = std::shared_ptr<Constant>;

	struct Constant {
		TypePtr type;
		ValuePtr value;
		ParAttrs parattrs;
		Conversion conversion = Conversion::None;
		ConstantPtr conversionSource = nullptr;
		TypePtr conversionType = nullptr;

		Constant() = delete;
		Constant(const Constant &) = delete;
		Constant(TypePtr, ValuePtr, const ParAttrs &, Conversion, ConstantPtr, TypePtr);
		Constant(const ASTNode *);

		ConstantPtr copy() const;
		operator std::string() const;
	};

	std::ostream & operator<<(std::ostream &, const Constant &);
}

#endif
