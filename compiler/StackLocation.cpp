#include "compiler/StackLocation.h"
#include "compiler/Variable.h"

namespace LL2W {
	StackLocation::StackLocation(std::shared_ptr<Variable> variable_): variable(variable_) {}
	StackLocation::StackLocation(LL2W::Type *type_): type(type_->copy()) {}

	Type * StackLocation::getType() const {
		return type? type.get() : variable->type;
	}

	std::string StackLocation::getName() const {
		return variable? "%" + std::to_string(variable->id) : "[" + std::string(*type) + "]";
	}
}
