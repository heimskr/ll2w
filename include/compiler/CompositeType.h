#pragma once

#include <string>

#include "compiler/LLVMType.h"

namespace LL2W {
	class ASTNode;

	struct CompositeType: LLVMType {
		int id;

		CompositeType() = delete;
		CompositeType(const ASTNode &);

		/** Composite types are things like classes and arrays that don't have signedness as an inherent property.
		 *  Or so I'm assuming... */
		bool isSigned(Program *) override { return false; }
	};
}
