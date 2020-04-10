#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AndIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"
#include "instruction/SubRInstruction.h"
#include "instruction/XorRInstruction.h"
#include "pass/LowerConversions.h"

namespace LL2W::Passes {
	int lowerConversions(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Conversion)
				continue;
			
			ConversionNode *conversion = dynamic_cast<ConversionNode *>(llvm->node);
			const Conversion type = conversion->conversionType;

			switch (type) {
				case Conversion::Bitcast:
				case Conversion::Zext:
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

	void lowerBasicConversion(Function &function, std::shared_ptr<Instruction> &instruction, ConversionNode *node) {
		if (!node->value->isLocal())
			throw std::runtime_error("Expected a pvar in " + conversion_map.at(node->conversionType) + " conversion");
		VariablePtr source = dynamic_cast<LocalValue *>(node->value.get())->variable;
		node->variable->setType(node->to);
		auto move = std::make_shared<MoveInstruction>(source, node->variable);
		function.insertBefore(instruction, move);
	}

	void lowerTrunc(Function &function, std::shared_ptr<Instruction> &instruction, ConversionNode *conversion) {
		if (!conversion->to->isInt())
			throw std::runtime_error("Trunc conversion expected to convert to an integer type");

		if (!conversion->value->isLocal())
			throw std::runtime_error("Expected a pvar in zext conversion");
		VariablePtr source = dynamic_cast<LocalValue *>(conversion->value.get())->variable;

		const int mask = (1 << conversion->to->width()) - 1;
		auto andi = std::make_shared<AndIInstruction>(source, mask, conversion->variable);
		function.insertBefore(instruction, andi);
	}

	void lowerSext(Function &function, std::shared_ptr<Instruction> &instruction, ConversionNode *conversion) {
		if (!conversion->from->isInt() || !conversion->to->isInt())
			throw std::runtime_error("Expected from and to types to be integer types in sext conversion");

		if (!conversion->value->isLocal())
			throw std::runtime_error("Expected a pvar in zext conversion");
		VariablePtr source = dynamic_cast<LocalValue *>(conversion->value.get())->variable;
		VariablePtr destination = conversion->variable;

		int from = conversion->from->width(), to = conversion->to->width();
		if (to == 64 || to == 32) {
			// Credit for formula: Sean Eron Anderson <seander@cs.stanford.edu>
			// http://graphics.stanford.edu/~seander/bithacks.html
			auto m0 = function.makeAssemblerVariable(0, instruction->parent.lock());
			// 1 -> $m0
			auto set1 = std::make_shared<SetInstruction>(m0, 1);
			// $m0 << (from - 1) -> $m0
			auto shift = std::make_shared<ShiftLeftLogicalIInstruction>(m0, from - 1, m0);
			// Now $m0 contains "m".
			// $src x $m0 -> $dst
			auto xorr = std::make_shared<XorRInstruction>(source, m0, destination);
			// $dst -= $m0
			auto sub = std::make_shared<SubRInstruction>(destination, m0, destination);
			for (const InstructionPtr &inst: std::initializer_list<InstructionPtr> {set1, shift, xorr, sub}) {
				function.insertBefore(instruction, inst);
				inst->extract();
			}

			if (to == 32) {
				auto andi = std::make_shared<AndIInstruction>(destination, 0xffffffff, destination);
				function.insertBefore(instruction, andi);
				andi->extract();
			}
		} else throw std::runtime_error("Sign extensions to widths other than 64 and 32 are currently unsupported");
		// TODO: support other destination widths
	}
}
