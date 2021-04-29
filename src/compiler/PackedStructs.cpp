#include "compiler/PackedStructs.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "instruction/DeferredDestinationMoveInstruction.h"
#include "instruction/DeferredSourceMoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/ShiftRightLogicalIInstruction.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"
#include "parser/StructNode.h"

/**
 * Example struct: {i8*, i8, i32, {i16, i64}, i8*, i32} (total width: 64 + 8 + 32 + 80 + 64 + 32 = 280)
 * Target index: 3 ({i16, i64})
 * Physical input registers: ($t0 $t1 $t2 $t3 $t4)
 * Target output registers: ($s0 $s1)
 * Contents:
 * 	i8*: 0x1234567890abcdef
 * 	i8:  0x66
 * 	i32: 0xaabbccdd
 * 	{i16, i64}: 0x1234, 0x1122334455667788
 * 	i8*: 0x1f2e3d4c5b6a7988
 * 	i32: 0x1a2a3a4a
 * 
 * 	$t0: 0x1234567890abcdef
 * 	$t1: 0x66aabbccdd123411
 * 	$t2: 0x223344556677881f
 * 	$t3: 0x2e3d4c5b6a79881a
 * 	$t4: 0x2a3a4a0000000000
 * 
 * 	$s0: 0x1234112233445566
 * 	$s1: 0x7788000000000000
 * 
 * Add up widths of preceding types (64 + 8 + 32 = 104)
 * Calculate total width remaining = width of target index (16 + 64 = 80)
 * Set width remaining for current register to 16???
 * 
 * While width sum > 64, subtract 64 and skip a physical register
 * (104, $t0) => (40, $t1)
 * 
 * - Skip 40 bits of $t1 and take min(64 - 40, 64 [rem. bits in $t1], 64 [rem. bits in $s1], 80) = 24 bits from $t1 and
 *   put them in the left of $s0
 * - $s0 = 0x1234110000000000
 *   (40, $t1) => (0,  $t2)
 *   (64, $s0) => (40, $s0)
 *   Total remaining: 80 - 24 = 56
 * - Skip 0 bits of $t2 and take min(64 - 0, 64 [rem. bits in $t2], 40 [rem. bits in $s1], 56) = 40 bits from $t2 and
 *   put them in the left + (64 - 40) bits of $s0
 * - $s0 = 0x1234112233445566
 *   (0,  $t2) => (40, $t2)
 *   (40, $s0) => (64, $s1)
 *   Total remaining: 56 - 40 = 16
 * - Skip 40 bits of $t2 and take min(64 - 40, 24 [rem. bits in $t2], 64 [rem. bits in $s1], 16) = 16 bits from $t2 and
 *   put them in the left + (64 - 64) bits of $s1
 * - $s1 = 0x7788000000000000
 */

namespace LL2W::PackedStructs {
	VariablePtr extract(VariablePtr source, int index, Function &function, InstructionPtr instruction) {
		std::list<int> source_regs(source->registers.begin(), source->registers.end());

		TypePtr type = source->type;
		if (!type)
			throw std::runtime_error("PackedStructs::extract: source variable has no type");
		
		StructType *initial_struct_type = dynamic_cast<StructType *>(type.get());
		if (!initial_struct_type)
			throw std::runtime_error("PackedStruct::extract: source variable type isn't StructType");

		auto struct_type = initial_struct_type->pad();

		index = struct_type->paddingMap.at(index);

		// TODO: support ArrayType

		int width_sum = 0;

		for (int i = 0; i < index; ++i) {
			width_sum += struct_type->node->types.at(i)->width();
		}

		int skip, source_reg_index = 0;

		info() << "Width sum: " << width_sum << "\n";

		// While 64 <= width sum, subtract 64 and skip a source register.
		// The result will be the number of bits to skip in the first used source register.
		for (skip = width_sum; 64 <= skip; skip -= 64)
			++source_reg_index;

		info() << "Skip: " << skip << ", source register index: " << source_reg_index << "\n";

		int target_remaining = 64;

		auto extracted_type = struct_type->node->types.at(index);

		const int extracted_width = extracted_type->width();

		int to_take = std::min({64 - skip, target_remaining, extracted_width});

		VariablePtr out_var = function.newVariable(extracted_type);

		info() << "outvar: " << *out_var << " (registers required: " << out_var->registersRequired() << ")\n";

		auto from_pack = function.newVariable();
		auto move_from_pack = std::make_shared<DeferredSourceMoveInstruction>(source, from_pack, source_reg_index);
		function.insertBefore(instruction, move_from_pack, false);
		function.comment(move_from_pack, "PackedStructs: move from pack");
		move_from_pack->extract();

		if (to_take != 64) {
			// Normally I'd use a mask and an AndIInstruction, but our mask would often be larger than the 32 bits
			// allowed in an I-type instruction's immediate value.
			auto destination = function.newVariable();
			auto right_shift = std::make_shared<ShiftRightLogicalIInstruction>(from_pack, 64 - to_take, destination);
			function.insertBefore(instruction, right_shift, false);
			right_shift->extract();
			auto left_shift = std::make_shared<ShiftLeftLogicalIInstruction>(destination, 64 - to_take, destination);
			function.insertBefore(instruction, left_shift, false);
			left_shift->extract();
		}




		function.reindexInstructions();
		return nullptr;
	}
}
