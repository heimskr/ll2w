#ifndef COMPILER_STACKLOCATION_H_
#define COMPILER_STACKLOCATION_H_

#include <memory>

#include "parser/Types.h"

namespace LL2W {
	class Variable;

	struct StackLocation {
		enum class Type {Spill, Alloca};
		
		int offset = 0, width = -1, align = -1;
		std::unique_ptr<LL2W::Type> type;
		std::shared_ptr<Variable> variable;

		StackLocation(std::shared_ptr<Variable> variable_, int offset_ = 0, int width_ = -1, int align_ = -1);
		StackLocation(LL2W::Type *type_, int offset_ = 0, int width_ = -1, int align_ = -1);

		LL2W::Type * getType() const;
		std::string getName() const;
	};
}

#endif
