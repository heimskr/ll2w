#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AndIInstruction.h"
#include "instruction/AndRInstruction.h"
#include "instruction/BitcastInstruction.h"
#include "instruction/LuiInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/SextRInstruction.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"
#include "instruction/ShiftRightLogicalIInstruction.h"
#include "instruction/SubIInstruction.h"
#include "instruction/SubRInstruction.h"
#include "instruction/XorRInstruction.h"
#include "pass/LowerConversions.h"
#include "util/Timer.h"
#include "util/Util.h"

namespace LL2W::Passes {
	template <typename I = MoveInstruction>
	void lowerBasicConversion(Function &function, InstructionPtr &instruction, ConversionNode *node) {
		if (!node->value->isLocal())
			throw std::runtime_error("Expected a pvar in " + conversion_map.at(node->conversionType) + " conversion");
		VariablePtr source = dynamic_cast<LocalValue *>(node->value.get())->variable;
		node->variable->setType(node->to);
		auto new_instruction = std::make_shared<I>(source, node->variable);
		function.insertBefore(instruction, new_instruction);
		new_instruction->setDebug(node)->extract();
	}

	size_t lowerConversions(Function &function) {
		Timer timer("LowerConversions");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->getNodeType() != NodeType::Conversion)
				continue;

			ConversionNode *conversion = dynamic_cast<ConversionNode *>(llvm->getNode());
			const Conversion type = conversion->conversionType;

			switch (type) {
				case Conversion::Bitcast:
					lowerBasicConversion<BitcastInstruction>(function, instruction, conversion);
					break;
				case Conversion::Zext:
				case Conversion::Ptrtoint:
				case Conversion::Inttoptr:
					lowerBasicConversion(function, instruction, conversion);
					break;
				case Conversion::Trunc:
					lowerTrunc(function, instruction, conversion);
					break;
				case Conversion::Sext:
					lowerSext(function, instruction, conversion);
					break;
				default:
					conversion->debug();
					throw std::runtime_error("Unsupported conversion: " + conversion_map.at(type));
			}

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}

	void lowerTrunc(Function &function, InstructionPtr &instruction, ConversionNode *conversion) {
		if (!conversion->to->isInt())
			throw std::runtime_error("Trunc conversion expected to convert to an integer type");

		if (!conversion->value->isLocal())
			throw std::runtime_error("Expected a pvar in zext conversion");
		VariablePtr source = dynamic_cast<LocalValue *>(conversion->value.get())->variable;
		VariablePtr destination = conversion->variable;

		const int from = conversion->from->width(), to = conversion->to->width();
		const std::string tag = std::to_string(from) + " to " + std::to_string(to);

		if (32 < to) {
			// If the number of bits to truncate to is greater than 32, we can't fit a mask in an immediate value.
			// Instead, we can shift left and then right by the same number of bits to clear the higher bits.
			auto left = std::make_shared<ShiftLeftLogicalIInstruction>(source, 64 - to, destination);
			auto right = std::make_shared<ShiftRightLogicalIInstruction>(destination, 64 - to, destination);
			function.insertBefore(instruction, left,  "LowerTrunc: " + tag + ", left shift");
			function.insertBefore(instruction, right, "LowerTrunc: " + tag + ", right shift");
			left->setDebug(conversion)->extract();
			right->setDebug(conversion)->extract();
		} else {
			const int mask = static_cast<int>((1L << conversion->to->width()) - 1);
			auto andi = std::make_shared<AndIInstruction>(source, mask, destination);
			function.insertBefore(instruction, andi, "LowerTrunc: " + tag + ", apply mask");
			andi->setDebug(conversion)->extract();
		}
	}

	void lowerSext(Function &function, InstructionPtr &instruction, ConversionNode *conversion) {
		if (!conversion->from->isInt() || !conversion->to->isInt())
			throw std::runtime_error("Expected from and to types to be integer types in sext conversion");

		if (!conversion->value->isLocal())
			throw std::runtime_error("Expected a pvar in zext conversion");
		VariablePtr source = dynamic_cast<LocalValue *>(conversion->value.get())->variable;
		VariablePtr destination = conversion->variable;

		const int from = conversion->from->width(), to = conversion->to->width();

		// TODO(typed): update properly for the new typed sext instructions

		if (from == 32 && to == 64) {
			function.insertBefore(instruction, std::make_shared<SextRInstruction>(source, destination))
				->setDebug(conversion)->extract();
		} else if (from == 16 && (to == 32 || to == 64)) {
			function.insertBefore(instruction, std::make_shared<SextRInstruction>(source, destination))
				->setDebug(conversion)->extract();
			if (to == 32)
				function.insertBefore(instruction, std::make_shared<LuiInstruction>(destination, 0))
					->setDebug(conversion)->extract();
		} else if (from == 8 && (to == 32 || to == 64)) {
			function.insertBefore(instruction, std::make_shared<SextRInstruction>(source, destination))
				->setDebug(conversion)->extract();
			if (to == 32)
				function.insertBefore(instruction, std::make_shared<LuiInstruction>(destination, 0))
					->setDebug(conversion)->extract();
		} else if (to == 64 || to == 32 || to == 16) {
			// Credit for formula: Sean Eron Anderson <seander@cs.stanford.edu>
			// http://graphics.stanford.edu/~seander/bithacks.html
			auto m0 = function.mx(0, instruction->parent.lock());
			// 1 -> $m0
			auto set1 = std::make_shared<SetInstruction>(m0, 1);
			// $m0 << (from - 1) -> $m0
			auto shift = std::make_shared<ShiftLeftLogicalIInstruction>(m0, from - 1, m0);
			// Now $m0 contains "m".
			// $src x $m0 -> $dst
			auto xorr = std::make_shared<XorRInstruction>(source, m0, destination);
			// $dst -= $m0
			auto sub = std::make_shared<SubRInstruction>(destination, m0, destination);
			for (const InstructionPtr &inst: std::initializer_list<InstructionPtr> {set1, shift, xorr, sub})
				function.insertBefore(instruction, inst)->setDebug(conversion)->extract();

			if (to == 32) {
				auto zero = function.makePrecoloredVariable(WhyInfo::zeroOffset, instruction->parent.lock());
				auto subi = std::make_shared<SubIInstruction>(zero, 1, m0);
				auto lui  = std::make_shared<LuiInstruction>(m0, 0);
				auto andi = std::make_shared<AndRInstruction>(destination, m0, destination);
				function.insertBefore(instruction, subi, "LowerSext: to == 32")->setDebug(conversion)->extract();
				function.insertBefore(instruction, lui)->setDebug(conversion)->extract();
				function.insertBefore(instruction, andi)->setDebug(conversion)->extract();
			}
		} else
			throw std::runtime_error("Sign extensions to widths other than 64 and 32 are currently unsupported (" +
				std::string(conversion->location) + ")");
		// TODO: support other destination widths
	}
}
