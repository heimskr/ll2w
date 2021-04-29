#include "compiler/PackedStructs.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Variable.h"
#include "instruction/DeferredDestinationMoveInstruction.h"
#include "instruction/DeferredSourceMoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/ShiftRightLogicalIInstruction.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"
#include "parser/Nodes.h"
#include "parser/StructNode.h"

namespace LL2W::PackedStructs {
	VariablePtr extract(VariablePtr source, int index, Function &function, InstructionPtr instruction) {
		std::list<int> source_regs(source->registers.begin(), source->registers.end());

		TypePtr type = source->type;
		if (!type)
			throw std::runtime_error("PackedStructs::extract: source variable has no type");
		
		StructType *initial_struct_type = dynamic_cast<StructType *>(type.get());
		if (!initial_struct_type)
			throw std::runtime_error("PackedStruct::extract: source variable type isn't StructType");

		LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
		if (!llvm)
			throw std::runtime_error("PackedStructs::extract not called on an LLVM instruction");

		ExtractValueNode *evnode = dynamic_cast<ExtractValueNode *>(llvm->node);
		if (!evnode)
			throw std::runtime_error("PackedStructs::extract not called on an extractvalue node");

		if (!evnode->variable->type)
			throw std::runtime_error("ExtractValueNode output variable has no type");

		auto struct_type = initial_struct_type->pad();
		index = struct_type->paddingMap.at(index);

		// TODO: support ArrayType

		int width_sum = 0;
		for (int i = 0; i < index; ++i)
			width_sum += struct_type->node->types.at(i)->width();

		int skip, source_reg_index = 0;

		// While 64 <= width sum, subtract 64 and skip a source register.
		// The result will be the number of bits to skip in the first used source register.
		for (skip = width_sum; 64 <= skip; skip -= 64)
			++source_reg_index;

		auto extracted_type = struct_type->node->types.at(index);
		int width_remaining = extracted_type->width();
		int target_remaining = 64;
		int target_reg_index = 0;

		VariablePtr out_var = evnode->variable;

		while (0 < width_remaining) {
			int to_take = std::min({64 - skip, target_remaining, width_remaining});
			auto from_pack = function.newVariable();
			auto move_from_pack = std::make_shared<DeferredSourceMoveInstruction>(source, from_pack, source_reg_index);
			function.insertBefore(instruction, move_from_pack, false);
			function.comment(move_from_pack, "PackedStructs(out = " + out_var->type->toString() + "): move from pack");
			move_from_pack->extract();

			if (skip != 0) {
				// Normally I'd use a mask and an AndIInstruction, but our mask would often be larger than the 32 bits
				// allowed in an I-type instruction's immediate value. What we're doing here is removing the bits we
				// skipped in the source register.
				auto left = std::make_shared<ShiftLeftLogicalIInstruction>(from_pack, skip, from_pack);
				function.insertBefore(instruction, left, false);
				left->extract();
				auto right = std::make_shared<ShiftRightLogicalIInstruction>(from_pack, skip, from_pack);
				function.insertBefore(instruction, right, false);
				right->extract();
			}

			if (skip + to_take < 64) {
				// Same applies here; instead of masking, we have to use two shifts. This time, we're removing the extra
				// bits to the right of the data we want.
				auto right = std::make_shared<ShiftRightLogicalIInstruction>(from_pack, 64 - skip - to_take, from_pack);
				function.insertBefore(instruction, right, false);
				right->extract();

				// If the output is, say, an i16 type, then we want the data to be right-aligned without the left
				// alignment we use for structs. We can accomplish that by simply not shifting it back to the left here.
				if (out_var->type->typeType() == TypeType::Struct) {
					auto left = std::make_shared<ShiftLeftLogicalIInstruction>(from_pack, 64 - skip - to_take,
						from_pack);
					function.insertBefore(instruction, left, false);
					left->extract();
				}
			}

			if (skip != 0) {
				auto left = std::make_shared<ShiftLeftLogicalIInstruction>(from_pack, skip, from_pack);
				function.insertBefore(instruction, left, false);
				left->extract();
			}

			auto move = std::make_shared<DeferredDestinationMoveInstruction>(from_pack, out_var, target_reg_index);
			function.insertBefore(instruction, move, false);
			move->extract();

			target_remaining -= to_take;
			width_remaining -= to_take;
			if (target_remaining < 0)
				warn() << "target_remaining (" << target_remaining << ") is less than zero!\n";

			if (target_remaining <= 0) {
				target_remaining = 64;
				++target_reg_index;
			}

			skip = 0;

			// I think this is valid. If the size of the extracted element is less than 64, then all the width is taken
			// care of in one iteration of this loop and this increment doesn't matter. Otherwise, the struct element
			// will be 64-byte aligned and we'll be taking 64 bits at a time (at least until the last iteration,
			// possibly).
			++source_reg_index;
		}

		function.reindexInstructions();
		return out_var;
	}
}
