#pragma once

#include <string>

#include "compiler/LLVMType.h"

namespace LL2W {
	class ASTNode;

	struct BasicType: LLVMType {
		int id = -1;
		int size = -1; // decimal
		const std::string *encoding = nullptr;

		BasicType(const ASTNode &node);

		bool isSigned(Program *) override;
	};
}
