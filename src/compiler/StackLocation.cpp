#include "compiler/StackLocation.h"
#include "compiler/Variable.h"

namespace LL2W {
	StackLocation::StackLocation(Function *function_, std::shared_ptr<Variable> variable_, int offset_, int width_,
	int align_):
		function(function_), offset(offset_), width(width_), align(align_), variable(variable_) {}

	StackLocation::StackLocation(Function *function_, LL2W::Type *type_, int offset_, int width_, int align_):
		function(function_), offset(offset_), width(width_), align(align_), type(type_->copy()) {}

	TypePtr StackLocation::getType() const {
		return type? type : variable->type;
	}

	std::string StackLocation::getName() const {
		return *variable;
	}

	bool StackLocation::operator==(const StackLocation &other) const {
		return function == other.function && offset == other.offset && width == other.width && align == other.align &&
			type == other.type && variable == other.variable;
	}
}
