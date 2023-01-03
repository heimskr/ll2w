#pragma once

#include <string>

namespace LL2W {
	class Program;

	struct LLVMType {
		int id = -1;
		const std::string *name = nullptr;

		virtual ~LLVMType() = default;
		virtual bool isSigned(Program *) = 0;

		protected:
			LLVMType(int id_ = -1, const std::string *name_ = nullptr): id(id_), name(name_) {}
			LLVMType(const std::string *name_): name(name_) {}
	};
}
