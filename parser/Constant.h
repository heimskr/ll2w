#ifndef PARSER_CONSTANT_H_
#define PARSER_CONSTANT_H_

#include <unordered_set>

#include "Enums.h"
#include "Types.h"
#include "Values.h"

namespace LL2W {
	class ASTNode;
	class Constant {
		private:
			Constant(Type *, Value *, const std::unordered_set<ParAttr> &, int, Conversion, Constant *, Type *);

		public:
			Type *type;
			Value *value;
			std::unordered_set<ParAttr> parattrs;
			int dereferenceable = -1;
			Conversion conversion = Conversion::None;
			Constant *conversionSource = nullptr;
			Type *conversionType = nullptr;

			Constant() = delete;
			Constant(const Constant &) = delete;
			Constant(ASTNode *);
			~Constant();
			Constant * copy() const;
			operator std::string() const;
	};
}

#endif
