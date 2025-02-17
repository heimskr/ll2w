#pragma once

#include <memory>

#include "parser/Types.h"

namespace LL2W {
	class Function;
	class Variable;

	struct StackLocation {
		enum class Purpose {Spill, Alloca, Clobber};
		
		Function *function = nullptr;
		Purpose purpose;
		int offset = 0;
		int width = -1; // in bytes?
		int align = -1;
		TypePtr type;
		std::shared_ptr<Variable> variable;

		StackLocation(Function *function_, std::shared_ptr<Variable> variable_, Purpose purpose_, int offset_ = 0,
			int width_ = -1, int align_ = -1);
		StackLocation(Function *function_, LL2W::Type *type_, Purpose purpose, int offset_ = 0, int width_ = -1,
			int align_ = -1);

		LL2W::TypePtr getType() const;
		std::string getName() const;

		bool operator==(const StackLocation &) const;
	};
}
