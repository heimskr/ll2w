#include "compiler/DerivedType.h"
#include "compiler/Program.h"
#include "exception/MissingTypeError.h"
#include "parser/ASTNode.h"
#include "parser/Constant.h"
#include "parser/Lexer.h"

#include <sstream>

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

	std::shared_ptr<LLVMType> DerivedType::getBaseType() const {
		if (!baseType)
			throw MissingTypeError("DerivedType " + std::to_string(id) + " has no base type");

		if (std::holds_alternative<int64_t>(*baseType))
			throw std::runtime_error("DerivedType " + std::to_string(id) + " has an integer base type; "
				"lookup is required");

		return std::get<std::shared_ptr<LLVMType>>(*baseType);
	}

	std::shared_ptr<LLVMType> DerivedType::getBaseType(Program &program) {
		if (!baseType)
			throw MissingTypeError("DerivedType " + std::to_string(id) + " has no base type");

		if (std::holds_alternative<int64_t>(*baseType)) {
			const auto type_index = std::get<int64_t>(*baseType);

			if (program.basicTypeSets.contains(type_index)) {
				auto typeset = program.basicTypeSets.at(type_index);
				baseType = typeset;
				return typeset;
			}

			if (program.compositeTypes.contains(type_index)) {
				auto composite = program.compositeTypes.at(type_index);
				baseType = composite;
				return composite;
			}

			if (program.derivedTypes.contains(type_index)) {
				auto derived = program.derivedTypes.at(type_index);
				baseType = derived;
				return derived;
			}

			throw std::runtime_error("DerivedType " + std::to_string(id) + " couldn't find DerivedType, TypeSet or "
				"CompositeType with index " + std::to_string(type_index));
		}

		return std::get<std::shared_ptr<LLVMType>>(*baseType);
	}

	Signedness DerivedType::getSignedness(Program *program) {
		try {
			auto base = program == nullptr? getBaseType() : getBaseType(*program);
			return base->getSignedness(program);
		} catch (const MissingTypeError &) {
			return Signedness::Unknown;
		}
	}

	DerivedType::operator std::string() {
		int base_type = -1;
		try {
			base_type = getBaseType()->id;
		} catch (const std::runtime_error &) {}

		std::ostringstream ss;
		ss << '!' << id << " = !DIDerivedType(tag: ";
		ss << (tag == nullptr? "null" : *tag);
		if (base_type != -1)
			ss << ", baseType: !" << base_type;
		if (file)
			ss << ", file: " << *file;
		if (line)
			ss << ", line: " << *line;
		if (scope)
			ss << ", scope: " << *scope;
		if (offset)
			ss << ", offset: " << *offset;
		if (size)
			ss << ", size: " << *size;
		if (align)
			ss << ", align: " << *align;
		if (!flags.empty()) {
			ss << ", flags: ";
			bool first = true;
			for (const std::string *flag: flags) {
				if (first)
					first = false;
				else
					ss << " | ";
				ss << *flag;
			}
		}
		if (extraData) {
			ss << ", extraData: ";
			if (std::holds_alternative<int64_t>(*extraData))
				ss << std::get<int64_t>(*extraData);
			else
				ss << *std::get<std::shared_ptr<Constant>>(*extraData);
		}
		ss << ')';
		return ss.str();
	}
}
