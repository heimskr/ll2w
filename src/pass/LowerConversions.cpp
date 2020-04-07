#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AndIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/LowerConversions.h"

namespace LL2W::Passes {
	int lowerConversions(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Conversion)
				continue;
			
			ConversionNode *conversion = dynamic_cast<ConversionNode *>(llvm->node);
			Conversion type = conversion->conversionType;

			bool remove = true;
			switch (type) {
				case Conversion::Bitcast:
				case Conversion::Zext:
					lowerBasicConversion(function, instruction, conversion);
					break;
				case Conversion::Trunc:
					lowerTrunc(function, instruction, conversion);
					break;
				default:
					remove = false;
					conversion->debug();
					// throw std::runtime_error("Unsupported conversion: " + conversion_map.at(type));
			}

			if (remove)
				to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}

	void lowerBasicConversion(Function &function, std::shared_ptr<Instruction> &instruction, ConversionNode *node) {
		if (!node->value->isLocal())
			throw std::runtime_error("Expected a pvar in " + conversion_map.at(node->conversionType) + " conversion");
		auto source = dynamic_cast<LocalValue *>(node->value.get())->variable;
		node->variable->setType(node->to);
		auto move = std::make_shared<MoveInstruction>(source, node->variable);
		function.insertBefore(instruction, move);
	}

	void lowerTrunc(Function &function, std::shared_ptr<Instruction> &instruction, ConversionNode *conversion) {
		if (!conversion->to->isInt())
			throw std::runtime_error("Trunc conversion expected to convert to an integer type");
		IntType *int_type = dynamic_cast<IntType *>(conversion->to.get());

		if (!conversion->value->isLocal())
			throw std::runtime_error("Expected a pvar in zext conversion");
		auto source = dynamic_cast<LocalValue *>(conversion->value.get())->variable;

		const int mask = (1 << int_type->intWidth) - 1;
		auto andi = std::make_shared<AndIInstruction>(source, mask, conversion->variable);
		function.insertBefore(instruction, andi);
	}
}
