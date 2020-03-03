#include "compiler/StackLocation.h"
#include "compiler/Variable.h"

namespace LL2W {
	StackLocation::StackLocation(std::shared_ptr<Variable> variable_, int offset_, int width_, int align_):
		offset(offset_), width(width_), align(align_), variable(variable_) {}

	StackLocation::StackLocation(LL2W::Type *type_, int offset_, int width_, int align_):
		offset(offset_), width(width_), align(align_), type(type_->copy()) {}

	Type * StackLocation::getType() const {
		return type? type.get() : variable->type;
	}

	std::string StackLocation::getName() const {
		return *variable;
	}
}
