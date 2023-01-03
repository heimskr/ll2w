#include "compiler/DerivedType.h"
#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/Constant.h"
#include "parser/Lexer.h"

namespace LL2W {
	DerivedType::DerivedType(const ASTNode &node): id(node.front()->atoi()) {
		for (const ASTNode *item: *node.back()) {
			const ASTNode &front = *item->front();
			switch (item->symbol) {
				case LLVMTOK_TAG:
					tag = front.lexerInfo;
					break;
				case LLVMTOK_SIZE:
					size = front.atoi();
					break;
				case LLVMTOK_BASETYPE:
					if (front.symbol == LLVMTOK_INTBANG)
						baseType = front.atoi();
					break;
				case LLVMTOK_NAME:
					name = front.lexerInfo;
					break;
				case LLVMTOK_FILE:
					file = front.atoi();
					break;
				case LLVMTOK_LINE:
					line = front.atoi();
					break;
				case LLVMTOK_SCOPE:
					scope = front.atoi();
					break;
				case LLVMTOK_OFFSET:
					offset = front.atoi();
					break;
				case LLVMTOK_FLAGS:
					for (const ASTNode *pipe: front)
						flags.insert(pipe->lexerInfo);
					break;
				case LLVMTOK_EXTRADATA:
					if (front.symbol == LLVM_CONSTANT)
						extraData = Constant::make(&front);
					else
						extraData = front.atoi();
					break;
				case LLVMTOK_ALIGN:
					align = front.atoi();
					break;
				default:
					throw std::runtime_error("Unrecognized symbol in DerivedType constructor: " +
						std::to_string(item->symbol));
			}
		}
	}

	std::shared_ptr<TypeSet> DerivedType::getBaseType() const {
		if (!baseType)
			throw std::runtime_error("DerivedType " + std::to_string(id) + " has no base type");

		if (std::holds_alternative<int64_t>(*baseType))
			throw std::runtime_error("DerivedType " + std::to_string(id) + " has an integer base type; "
				"lookup is required");

		return std::get<std::shared_ptr<TypeSet>>(*baseType);
	}

	std::shared_ptr<TypeSet> DerivedType::getBaseType(Program &program) {
		if (!baseType)
			throw std::runtime_error("DerivedType " + std::to_string(id) + " has no base type");

		if (std::holds_alternative<int64_t>(*baseType)) {
			const auto type_index = std::get<int64_t>(*baseType);

			if (program.basicTypeSets.contains(type_index)) {
				auto typeset = program.basicTypeSets.at(type_index);
				baseType = typeset;
				return typeset;
			}

			if (program.compositeTypes.contains(type_index)) {
				
			}

			throw std::runtime_error("DerivedType " + std::to_string(id) + " couldn't find typeset or composite with "
				"index " + std::to_string(type_index));
		}

		return std::get<std::shared_ptr<TypeSet>>(*baseType);
	}

	bool DerivedType::isSigned(Program *program) {
		std::shared_ptr<TypeSet> typeset = program == nullptr? getBaseType() : getBaseType(*program);
		std::optional<bool> is_signed;
		for (const auto &type: *typeset) {
			const bool type_is_signed = type->isSigned(program);
			if (is_signed.has_value()) {
				if (*is_signed != type_is_signed)
					throw std::runtime_error("DerivedType " + std::to_string(id) + " has conflicting signednesses");
			} else
				is_signed = type_is_signed;
		}

		if (!is_signed.has_value())
			throw std::runtime_error("Couldn't find signedness for DerivedType " + std::to_string(id));

		return *is_signed;
	}
}
