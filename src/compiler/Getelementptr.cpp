#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/PaddedStructs.h"
#include "compiler/Program.h"
#include "compiler/Variable.h"
#include "exception/TypeError.h"
#include "instruction/AddIInstruction.h"
#include "instruction/AddRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/MultRInstruction.h"
#include "parser/Types.h"
#include "parser/StructNode.h"
#include "parser/Values.h"

namespace LL2W::Getelementptr {
	int64_t compute_mutating(TypePtr type, std::list<int64_t> &indices, TypePtr *out_type) {
		if (indices.empty()) {
			if (out_type) {
				*out_type = PointerType::make(type->copy());
			}
			return 0;
		}

		const int64_t front = indices.front();
		indices.pop_front();
		switch (type->typeType()) {
			case TypeType::Pointer:
			case TypeType::Array: {
				TypePtr subtype = dynamic_cast<HasSubtype *>(type.get())->subtype;
				return front * subtype->width() + compute_mutating(subtype, indices, out_type);
			}
			case TypeType::Struct: {
				std::shared_ptr<StructType> stype = std::dynamic_pointer_cast<StructType>(type);
				if (!stype->types) {
					stype = StructType::knownStructs.at(stype->barename());
				}
				return PaddedStructs::getOffset(stype, front) + compute_mutating(stype->types.value().at(front), indices, out_type);
			}
			default:
				throw TypeError("Getelementptr::compute encountered an invalid type: " + std::string(*type), type);
		}
	}

	void insert_mutating(Function &function, TypePtr type, std::list<std::variant<int64_t, const std::string *>> &indices, InstructionPtr &instruction, VariablePtr &out_var, TypePtr *out_type) {
		// TODO: add a bool first parameter, which if true indicates that out_var should be directly set to the computed
		// offset instead of being added to by the computed offset. This would obviate the need to set out_var to zero
		// at the beginning of the insert functions.

		if (indices.empty()) {
			if (out_type) {
				*out_type = PointerType::make(type->copy());
			}
			return;
		}

		using variant = std::variant<int64_t, const std::string *>;
		const variant front = indices.front();
		indices.pop_front();
		switch (type->typeType()) {
			case TypeType::Pointer:
			case TypeType::Array: {
				TypePtr subtype = dynamic_cast<HasSubtype *>(type.get())->subtype;
				const int64_t subbytes = Util::updiv(subtype->width(), 8);
				if (std::holds_alternative<int64_t>(front)) {
					const int64_t offset = std::get<int64_t>(front) * subbytes;
					InstructionPtr add;

					if (Util::outOfRange(offset)) {
						add = AddRInstruction::make(out_var, function.get64(instruction, offset), out_var);
					} else if (offset != 0) {
						add = AddIInstruction::make(out_var, int(offset), out_var);
					}

					if (add) {
						function.insertBefore(instruction, add)->setDebug(*instruction, true);
					}
				} else {
					VariablePtr m8 = function.mx(8, instruction);
					function.insertBefore(instruction, MultIInstruction::make(function.getVariable(std::get<const std::string *>(front), false), int(subbytes)))->setDebug(*instruction, true);
					function.insertBefore(instruction, MoveInstruction::make(function.lo(instruction), m8))->setDebug(*instruction, true);
					function.insertBefore(instruction, AddRInstruction::make(out_var, m8, out_var))->setDebug(*instruction, true);
				}
				insert_mutating(function, subtype, indices, instruction, out_var, out_type);
				break;
			}
			case TypeType::Struct: {
				if (!std::holds_alternative<int64_t>(front)) {
					throw std::runtime_error("Unable to index a struct with a pvar except in the first position");
				}
				std::shared_ptr<StructType> stype = std::dynamic_pointer_cast<StructType>(type);
				if (!stype->types) {
					stype = StructType::knownStructs.at(stype->barename());
				}
				const int64_t index = std::get<int64_t>(front);
				const int64_t offset = Util::updiv(PaddedStructs::getOffset(stype, index), 8);
				// Too lazy to handle overflows here.
				if (Util::outOfRange(offset)) {
					warn() << "PaddedStructs offset " << offset << " is out of the integer range. Incorrect code will be produced.\n";
				}
				if (offset != 0) {
					function.insertBefore(instruction, AddIInstruction::make(out_var, int(offset), out_var))->setDebug(*instruction, true);
				}
				insert_mutating(function, stype->types.value().at(index), indices, instruction, out_var, out_type);
				break;
			}
			default:
				throw TypeError("Getelementptr::insert encountered an invalid type: " + std::string(*type) + " (" + type_map.at(type->typeType()) + ")", type);
		}
	}

	int64_t compute(TypePtr type, std::list<int64_t> indices, TypePtr *out_type) {
		return compute_mutating(type, indices, out_type);
	}

	int64_t compute(const GetelementptrValue *value, TypePtr *out_type) {
		std::list<int64_t> indices = getLongIndices(*value);
		return compute_mutating(value->ptrType, indices, out_type);
	}

	void insert(Function &function, TypePtr type, std::list<std::variant<int64_t, const std::string *>> indices, InstructionPtr instruction, VariablePtr &out_var, TypePtr *out_type) {
		if (!out_var) {
			// out_var = function.newVariable(IntType::make(64), instruction->parent.lock());
			throw std::invalid_argument("out_var must not be null in Getelementptr::insert");
		}
		insert_mutating(function, type, indices, instruction, out_var, out_type);
	}

	void insert(Function &function, const GetelementptrValue *value, std::shared_ptr<Instruction> instruction, VariablePtr &out_var, TypePtr *out_type) {
		auto indices = getVariantIndices(*value);
		if (!out_var) {
			// out_var = function.newVariable(IntType::make(64), instruction->parent.lock());
			throw std::invalid_argument("out_var must not be null in Getelementptr::insert");
		}
		insert_mutating(function, value->ptrType, indices, instruction, out_var, out_type);
	}

	std::list<int64_t> getLongIndices(const GetelementptrValue &value) {
		std::list<int64_t> indices;
		for (const auto &decimal_pair: value.decimals) {
			if (!std::holds_alternative<int64_t>(decimal_pair.second)) {
				warn() << "GetelementptrValue decimal's second item is a pvar. Incorrect code will be produced.\n";
				indices.push_back(0);
			} else {
				indices.push_back(std::get<int64_t>(decimal_pair.second));
			}
		}
		return indices;
	}

	std::list<std::variant<int64_t, const std::string *>> getVariantIndices(const GetelementptrValue &value) {
		std::list<std::variant<int64_t, const std::string *>> indices;
		for (const auto &decimal_pair: value.decimals) {
			indices.push_back(decimal_pair.second);
		}
		return indices;
	}

	TypePtr findType(const TypePtr &source_type, std::span<int64_t> indices) {
		assert(!indices.empty());

		TypePtr type = PointerType::make(source_type);

		for (const int64_t index: indices) {
			switch (type->typeType()) {
				case TypeType::Array:
				case TypeType::Pointer:
					type = dynamic_cast<HasSubtype &>(*type).subtype;
					break;
				case TypeType::Struct: {
					auto struct_type = std::dynamic_pointer_cast<StructType>(type);
					assert(struct_type != nullptr);
					assert(struct_type->types.has_value());
					if (index < 0) {
						throw std::runtime_error("Known index required for struct in Getelementptr::findType");
					}
					type = struct_type->types->at(index);
					break;
				}
				default:
					error() << *type;
					throw std::runtime_error("Invalid type in Getelementptr::findType");
			}
		}

		return type;
	}
}