#include <deque>

#include "compiler/Function.h"
#include "compiler/Getelementptr.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/AddIInstruction.h"
#include "instruction/AddRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/MultIInstruction.h"
#include "instruction/SetInstruction.h"
#include "parser/StructNode.h"
#include "pass/LowerGetelementptr.h"
#include "util/Timer.h"
#include "util/Util.h"

// #define DEBUG_GETELEMENTPTR

namespace LL2W::Passes {
	static bool anyPvarInIndices(const std::vector<GetelementptrNode::Index> &indices) {
		for (const auto &index: indices)
			if (index.isPvar)
				return true;
		return false;
	}

	int lowerGetelementptr(Function &function) {
		Timer timer("LowerGetelementptr");
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

			ValuePtr constant_value = node->allValues().front();
			TypePtr constant_type = node->constant->convert()->type;

			if (!constant_value->isLocal() && !constant_value->isGlobal())
				throw std::runtime_error("Expected a pvar or gvar as the pointer value in a getelementptr instruction");

			VariablePtr pointer;
			if (constant_value->isLocal())
				pointer = dynamic_cast<LocalValue *>(constant_value.get())->variable;
			else {
				GlobalValue *global = dynamic_cast<GlobalValue *>(constant_value.get());
				pointer = function.newVariable(constant_type);
				function.insertBefore(instruction, std::make_shared<SetInstruction>(pointer, global->name))
					->setDebug(node);
			}

			const TypeType tt = constant_type->typeType();
			const bool one_pvar = node->indices.size() == 1 && node->indices.at(0).isPvar;
			const bool any_pvar = anyPvarInIndices(node->indices);
			const bool dynamic_index = node->indices.size() == 2 && !node->indices[0].isPvar && node->indices[1].isPvar;

			if (tt == TypeType::Struct && any_pvar) {
				// If there are any pvars in the index list, we can't combine all the indices into a single constant and
				// have to break the offset addition into separate steps for each index. Sequential constant (non-pvar)
				// indices could be combined into one addition, but I'm too lazy for that as of this writing.
				std::deque<GetelementptrNode::Index> indices(node->indices.begin(), node->indices.end());
				TypePtr type = constant_type;
				VariablePtr var = node->variable;
				VariablePtr lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());
				auto move = std::make_shared<MoveInstruction>(pointer, var);
				function.insertBefore(instruction, move, "LowerGetelementptr(" + std::string(node->location) +
					"): initial move -> " + var->plainString())->setDebug(node)->extract();
				while (!indices.empty()) {
					const auto &index = indices.front();
					indices.pop_front();
					const TypeType tt = type->typeType();
					if (index.isPvar) {
						VariablePtr pvar = std::holds_alternative<Variable::ID>(index.value)?
							  function.getVariable(std::get<Variable::ID>(index.value))
							: function.getVariable(std::to_string(std::get<long>(index.value)));
						if (tt == TypeType::Pointer || tt == TypeType::Array) {
							type = dynamic_cast<HasSubtype *>(type.get())->subtype;
							auto mult = std::make_shared<MultIInstruction>(pvar, type->width());
							auto add = std::make_shared<AddRInstruction>(var, lo, var);
							function.insertBefore(instruction, mult, "LowerGetelementptr(" + std::string(node->location)
								+ "): pointer/array, pvar -> " + var->plainString())->setDebug(node)->extract();
							function.insertBefore(instruction, add)->setDebug(node)->extract();
						} else if (tt == TypeType::Struct) {
							throw std::runtime_error("pvar indices are invalid for struct types @ " +
								std::string(node->location));
						}
					} else if (tt == TypeType::Pointer || tt == TypeType::Array) {
						type = dynamic_cast<HasSubtype *>(type.get())->subtype;
						auto add = std::make_shared<AddIInstruction>(var,
							int(type->width() * std::get<long>(index.value)), var);
						function.insertBefore(instruction, add, "LowerGetelementptr(" + std::string(node->location) +
							"): pointer/array, number -> " + var->plainString())->setDebug(node)->extract();
					} else if (tt == TypeType::Struct) {
						std::shared_ptr<StructType> stype = std::dynamic_pointer_cast<StructType>(type);
						std::shared_ptr<StructNode> snode = stype->node;
						if (!snode) {
							stype = StructType::knownStructs.at(stype->barename());
							snode = stype->node;
						}

						std::list<long> index_list;
						for (const GetelementptrNode::Index &index: indices)
							index_list.push_back(std::get<long>(index.value));

						TypePtr out_type;
						long offset = Util::updiv(Getelementptr::compute(constant_type, index_list, &out_type), 8l);
						if (Util::outOfRange(offset))
							warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';
						var->type = out_type;

						auto add = std::make_shared<AddIInstruction>(var, int(offset), var);
						function.insertBefore(instruction, add, "LowerGetelementptr(" + std::string(node->location) +
							"): struct, number -> " + var->plainString())->setDebug(node)->extract();
						type = snode->types.at(std::get<long>(index.value));
					} else
						throw std::runtime_error("Invalid type in GetelementPtr: " + std::string(*type));
				}

				node->type = var->type = std::make_shared<PointerType>(type->copy());
			} else if ((tt == TypeType::Array || tt == TypeType::Pointer) && dynamic_index) {
				// result = (base pointer) + (width * first index value) + (subwidth * second index variable)
				const int skip = Util::updiv(node->type->width(), 8) * std::get<long>(node->indices[0].value);
				VariablePtr index = function.getVariable(std::get<Variable::ID>(node->indices[1].value));
				VariablePtr lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());

				int subwidth;
				if (HasSubtype *has_subtype = dynamic_cast<HasSubtype *>(node->type.get())) {
					subwidth = Util::updiv(has_subtype->subtype->width(), 8);
				} else
					throw std::runtime_error("Type " + std::string(*node->type) + " has no subtype");

				// index * width
				auto mult = std::make_shared<MultIInstruction>(index, subwidth);
				// $lo -> result
				auto movelo = std::make_shared<MoveInstruction>(lo, node->variable);
				// result += skip
				auto addskip = std::make_shared<AddIInstruction>(node->variable, skip, node->variable);
				// result += base pointer
				auto add = std::make_shared<AddRInstruction>(node->variable, pointer, node->variable);
				function.insertBefore(instruction, mult, "LowerGetelementptr(" + std::string(node->location) +
					"): array/pointer-type, dynamic index -> " + node->variable->plainString());
				function.insertBefore(instruction, movelo)->setDebug(node)->extract();
				function.insertBefore(instruction, addskip)->setDebug(node)->extract();
				function.insertBefore(instruction, add)->setDebug(node)->extract();
				mult->setDebug(node)->extract();
			} else if (tt == TypeType::Struct || ((tt == TypeType::Array || tt == TypeType::Pointer) && !one_pvar)) {
				// Gather all the indices while making sure they're all decimals.
				std::list<long> indices;
				size_t index_count = 0;
				Variable::ID first_pvar = nullptr;
				for (const auto &index: node->indices) {
					++index_count;
					// It's always okay for the first index to be a pvar, even for structs, because it reaches not
					// within the struct but rather into the abyss beyond.
					if (index.isPvar) {
						if (1 < index_count) {
							node->debug();
							throw std::runtime_error("Unable to index a struct with a pvar except in the first "
								"position");
						} else {
							first_pvar = std::get<Variable::ID>(index.value);
							// Insert a dummy 0 value to make Getelementptr::compute still work.
							indices.push_back(0l);
							continue;
						}
					}
					indices.push_back(std::get<long>(index.value));
				}

				TypePtr out_type;
#ifdef DEBUG_GETELEMENTPTR
				TypePtr old_type = node->variable->type;
#endif
				if (node->location.line == 1300)
					std::cerr << "<SPECIAL>\n";
				long offset = Util::updiv(Getelementptr::compute(constant_type, indices, &out_type), 8l);
				if (Util::outOfRange(offset))
					warn() << "Getelementptr offset inexplicably out of range: " << offset << '\n';
				node->variable->type = out_type;
				node->type = out_type;
				if (node->location.line == 1300)
					std::cerr << "</SPECIAL>\n";

				auto add = std::make_shared<AddIInstruction>(pointer, int(offset), node->variable);
				function.insertBefore(instruction, add, "LowerGetelementptr(" + std::string(node->location) +
					"): struct-type: " + constant_type->toString() + " -> " + node->variable->plainString() +
					", offset=" + std::to_string(offset) + ", indices=" + Util::join(indices, ","))
					->setDebug(node)->extract();
				if (first_pvar) {
					auto pvar = function.getVariable(first_pvar);
					auto lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());
					auto mult = std::make_shared<MultIInstruction>(pvar, constant_type->width());
					auto second_add = std::make_shared<AddRInstruction>(node->variable, lo, node->variable);
					function.insertBefore(instruction, mult);
					function.insertBefore(instruction, second_add);
				}
#ifdef DEBUG_GETELEMENTPTR
				function.comment(add, "Type: " + std::string(*old_type) + " -> " + std::string(*out_type));
#endif
			} else if ((tt == TypeType::Array || tt == TypeType::Pointer) && one_pvar) {
				// result = (base pointer) + (width * index value)
				VariablePtr index = function.getVariable(std::get<Variable::ID>(node->indices.at(0).value));
				VariablePtr lo = function.makePrecoloredVariable(WhyInfo::loOffset, instruction->parent.lock());
				const int width = Util::updiv(node->type->width(), 8);
				// index * width
				auto mult = std::make_shared<MultIInstruction>(index, width);
				// $lo -> result
				auto movelo = std::make_shared<MoveInstruction>(lo, node->variable);
				// result += base pointer
				auto add = std::make_shared<AddRInstruction>(node->variable, pointer, node->variable);
				function.insertBefore(instruction, mult, "LowerGetelementptr(" + std::string(node->location) +
					"): pointer-type -> " + node->variable->plainString())->setDebug(node)->extract();
				function.insertBefore(instruction, movelo)->setDebug(node)->extract();
				function.insertBefore(instruction, add)->setDebug(node)->extract();
			} else throw std::runtime_error("Unsupported type in getelementptr instruction: " + type_map.at(tt));

			to_remove.push_back(instruction);
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
