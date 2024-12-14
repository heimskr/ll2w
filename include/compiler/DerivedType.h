#pragma once

#include <memory>
#include <optional>
#include <set>
#include <string>
#include <variant>

#include "compiler/LLVMType.h"

namespace LL2W {
	class  ASTNode;
	class Constant;
	class  Program;
	struct TypeSet;

	class DerivedType: public LLVMType {
		public:
			int64_t id = -1;
			const std::string *tag = nullptr;
			std::optional<int64_t> file;     // intbang
			std::optional<int64_t> line;     // decimal
			std::optional<int64_t> scope;    // intbang
			std::optional<int64_t> offset;   // decimal
			std::optional<int64_t> size;     // decimal
			std::optional<int64_t> align;    // decimal
			std::set<const std::string *> flags;
			std::optional<std::variant<int64_t, std::shared_ptr<Constant>>> extraData; // constant or intbang

			DerivedType(const ASTNode &node);

			std::shared_ptr<LLVMType> getBaseType() const;
			std::shared_ptr<LLVMType> getBaseType(Program &);

			Signedness getSignedness(Program *) override;
			operator std::string() override;

		private:
			/** If empty, then the base type is either "null" or unspecified. */
			std::optional<std::variant<int64_t, std::shared_ptr<LLVMType>>> baseType;
	};
}
