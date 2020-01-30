#ifndef PARSER_CONSTANT_H_
#define PARSER_CONSTANT_H_

#include <unordered_set>

#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "ParAttrs.h"

namespace LL2W {
	class ASTNode;
	class Constant {
		private:
			Constant(Type *, Value *, const ParAttrs &, Conversion, Constant *, Type *);

		public:
			Type *type;
			Value *value;
			ParAttrs parattrs;
			Conversion conversion = Conversion::None;
			Constant *conversionSource = nullptr;
			Type *conversionType = nullptr;

			Constant() = delete;
			Constant(const Constant &) = delete;
			Constant(const ASTNode *);
			~Constant();
			Constant * copy() const;
			operator std::string() const;
	};

	std::ostream & operator<<(std::ostream &, const Constant &);
}

#endif
