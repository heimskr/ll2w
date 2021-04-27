#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/AddRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/LowerGetelementptr.h"
#include "util/Util.h"

namespace LL2W::Passes {
	int lowerGetelementptr(Function &function) {
		using IndexTuple = std::tuple<int, int, bool, bool>;
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm || llvm->node->nodeType() != NodeType::Getelementptr)
				continue;

			GetelementptrNode *node = dynamic_cast<GetelementptrNode *>(llvm->node);
			// In all the getelementptr instructions I've seen, the source argument has always been a pvar, never a
			// gvar. The indices have been either two decimals or one pvar, but this could be just a quirk of the
			// example program I've been using (ll/fat.ll), as most of the types are the same struct type. However, I
			// see the same thing in ll/main.ll, and it makes sense: if one of the indices isn't known at compile time,
			// it wouldn't make much sense for it to be anywhere except at the end of a list of decimals.
			// ...after reviewing the documentation, it seems that only constant decimals are valid for structs, while
			// pvars are valid for pointers, arrays and vectors. This makes sense.

			// Update: I've since encountered a gvar as a source argument:
			//     %9 = getelementptr inbounds [200 x i8], [200 x i8]* @_ZNSt3__16__itoaL10cDigitsLutE, i64 0, i64 %8

			if (!node->ptrValue->isLocal() && !node->ptrValue->isGlobal())
				throw std::runtime_error("Expected a pvar or gvar as the pointer value in a getelementptr instruction");

			VariablePtr pointer;
			if (node->ptrValue->isLocal())
				pointer = dynamic_cast<LocalValue *>(node->ptrValue.get())->variable;
			else {
				GlobalValue *global = dynamic_cast<GlobalValue *>(node->ptrValue.get());
				pointer = function.newVariable(node->ptrType);
				warn() << "global[" << *global->name << "]\n";
				throw std::runtime_error("Globals not supported in LowerGetelementptr yet");
				// function.insertBefore(instruction, std::make_shared<SetInstruction>(pointer, global->name));
			}

			const TypeType tt = node->ptrType->typeType();
			const bool one_pvar = node->indices.size() == 1 && std::get<3>(node->indices.at(0));
			if (tt == TypeType::Struct || ((tt == TypeType::Array || tt == TypeType::Pointer) && !one_pvar)) {
				// Gather all the indices while making sure they're all decimals.
				std::list<int> indices;
				for (const IndexTuple &tuple: node->indices) {
					if (std::get<3>(tuple) && tt == TypeType::Struct) {
						node->debug();
						throw std::runtime_error("Unable to index a struct with a pvar");
					}
					indices.push_back(std::get<1>(tuple));
				}

				TypePtr out_type;
				const int offset = Util::updiv(Getelementptr::compute(node->ptrType, indices, &out_type), 8);
				auto add = std::make_shared<AddIInstruction>(pointer, offset, node->variable);
				function.insertBefore(instruction, add, "LowerGetelementptr: struct-type");
				add->extract();
			} else if ((tt == TypeType::Array || tt == TypeType::Pointer) && one_pvar) {
				// result = (base pointer) + (width * index value)
				VariablePtr index = function.getVariable(std::get<1>(node->indices.at(0)));
				VariablePtr lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());
				const int width = Util::updiv(node->type->width(), 8);
				// index * width
				auto mult = std::make_shared<MultIInstruction>(index, width);
				// $lo -> result
				auto movelo = std::make_shared<MoveInstruction>(lo, node->variable);
				// result += base pointer
				auto add = std::make_shared<AddRInstruction>(node->variable, pointer, node->variable);
				function.insertBefore(instruction, mult);
				function.insertBefore(instruction, movelo);
				function.insertBefore(instruction, add);
				mult->extract();
				movelo->extract();
				add->extract();
			} else throw std::runtime_error("Unsupported type in getelementptr instruction: " + type_map.at(tt));

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
