#include "compiler/Function.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/PrintPseudoinstruction.h"
#include "instruction/SetInstruction.h"
#include "parser/StructNode.h"
#include "pass/LowerInsertvalue.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t lowerInsertvalue(Function &function) {
		Timer timer("LowerInsertvalue");
		size_t changed = 0;

		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::InsertValue)
				continue;

			InsertValueNode *iv = dynamic_cast<InsertValueNode *>(llvm->node);

			// TODO: Actually implement this instead of using this dodgy hack to get optimized Thurisaz to compile.
			// For now, we support structs containing some number of integers of width <= 64. Each item in the
			// struct gets its own register; we don't compact e.g. eight i8s into one register. All the structs I've
			// seen for insertvalues so far are {i64}, {i64, i64} or {i8}.

			const ValueType avtype = iv->aggregateValue->valueType();

			if (iv->aggregateType->typeType() != TypeType::Struct) {
				warn() << "Skipping non-struct insertvalue: " << instruction->debugExtra() << '\n';
				continue;
			}

			StructType *aggregate_struct = dynamic_cast<StructType *>(iv->aggregateType.get());

			if (aggregate_struct->node->types.empty()) {
				warn() << "Skipping insertvalue with empty type: " << instruction->debugExtra() << '\n';
				continue;
			}

			if (iv->decimals.size() != 1) {
				warn() << "Skipping insertvalue with unsupported decimals: " << instruction->debugExtra() << '\n';
				continue;
			}

			bool skip = false;
			for (const auto &type: aggregate_struct->node->types)
				if (type->typeType() != TypeType::Int) {
					skip = true;
					break;
				}

			if (skip) {
				warn() << "Skipping unsupported insertvalue: " << instruction->debugExtra() << '\n';
				continue;
			}

			VariablePtr destination = function.variableStore.at(iv->result);
			// std::cerr << "Destination registers required: " << destination->registersRequired() << " -> " << destination->registersString() << "\n";
			VariablePtr reg = function.makePrecoloredVariable(*std::next(destination->registers.begin(),
				iv->decimals.front()), instruction->parent.lock());

			if (avtype == ValueType::Undef || avtype == ValueType::Local) {
				ValuePtr value = iv->value;
				ValueType valuetype = value->valueType();
				const std::string comment = " -> " + destination->registersString() + "[" +
					std::to_string(iv->decimals.front()) + "]";
				if (value->isIntLike()) {
					auto set = std::make_shared<SetInstruction>(reg, value->intValue(false));
					set->setOriginalValue(value);
					function.insertBefore(instruction, set, "LowerInsertvalue: intlike" + comment);
				} else if (valuetype == ValueType::Local) {
					VariablePtr source = dynamic_cast<LocalValue *>(value.get())->variable;
					auto move = std::make_shared<MoveInstruction>(source, reg);
					function.insertBefore(instruction, move, "LowerInsertvalue: local: " + source->plainString() +
						comment);
					// function.insertBefore(move, std::make_shared<PrintPseudoinstruction>("@"));
				} else {
					warn() << "Skipping insertvalue with unsupported value type: " << instruction->debugExtra() << '\n';
					continue;
				}
			} else {
				warn() << "Skipping insertvalue with unsupported avtype: " << instruction->debugExtra() << '\n';
				continue;
			}

			to_remove.push_back(instruction);
			++changed;
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return changed;
	}
}
