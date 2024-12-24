#pragma once

#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "ParAttrs.h"
#include "util/Makeable.h"

#include <memory>
#include <unordered_set>

namespace llvm {
	class Value;
}

namespace LL2W {
	class ASTNode;
	class Program;

	class Constant;
	using ConstantPtr = std::shared_ptr<Constant>;

	class Constant: public Makeable<Constant> {
		public:
			TypePtr type;
			ValuePtr value;
			ParAttrs parattrs;
			Conversion conversion = Conversion::None;
			ConstantPtr conversionSource = nullptr;
			TypePtr conversionType = nullptr;

			Constant(const Constant &) = delete;
			Constant(TypePtr, ValuePtr);
			Constant(TypePtr, ValuePtr, const ParAttrs &, Conversion, ConstantPtr, TypePtr);
			Constant(const ASTNode *, TypePtr type_hint = nullptr);

			ConstantPtr copy() const;
			/** Applies ptrtoint/inttoptr conversions and returns a new Constant. */
			ConstantPtr convert() const;
			operator std::string() const;

			static ConstantPtr fromLLVM(const llvm::Value &);

			TypePtr refineType(const Program &) const;

		private:
			Constant();
	};

	std::ostream & operator<<(std::ostream &, const Constant &);
}
