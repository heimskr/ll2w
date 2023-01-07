#pragma once

#include <string>

#include "parser/Enums.h"

namespace LL2W {
	class Program;

	struct LLVMType {
		int id = -1;
		const std::string *name = nullptr;

		virtual ~LLVMType() = default;
		virtual Signedness getSignedness(Program *) = 0;
		virtual operator std::string() = 0;

		protected:
			LLVMType(int id_ = -1, const std::string *name_ = nullptr): id(id_), name(name_) {}
			LLVMType(const std::string *name_): name(name_) {}
	};
}
