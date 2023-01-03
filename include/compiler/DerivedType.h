#pragma once

#include <memory>
#include <optional>
#include <set>
#include <string>
#include <variant>

namespace LL2W {
	class ASTNode;
	struct Constant;

	struct DerivedType {
		int64_t id = -1;
		const std::string *tag = nullptr;
		const std::string *name = nullptr;
		/** If empty, then the base type is either "null" or unspecified. */
		std::optional<int64_t> baseType;
		std::optional<int64_t> file;     // intbang
		std::optional<int64_t> line;     // decimal
		std::optional<int64_t> scope;    // intbang
		std::optional<int64_t> offset;   // decimal
		std::optional<int64_t> size;     // decimal
		std::optional<int64_t> align;    // decimal
		std::set<const std::string *> flags;
		std::optional<std::variant<std::shared_ptr<Constant>, int64_t>> extraData; // constant or intbang

		DerivedType(const ASTNode &node);
	};
}
