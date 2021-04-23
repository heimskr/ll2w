#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/WhyInfo.h"
#include "pass/LowerInlineAsm.h"
#include "util/Util.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "wasm/Nodes.h"
#include "instruction/Comment.h"
#include "instruction/SetInstruction.h"

namespace LL2W::Passes {
	int lowerInlineAsm(Function &function) {
		std::list<InstructionPtr> to_remove;

		int count = 0;

		for (auto iter = function.linearInstructions.begin(); iter != function.linearInstructions.end(); ++iter) {
			LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(iter->get());
			if (!llvm || llvm->node->nodeType() != NodeType::Asm)
				continue;

			++count;
			AsmNode *asm_node = dynamic_cast<AsmNode *>(llvm->node);

			wasmParser.in(asm_node->contents->substr(1, asm_node->contents->size() - 2));
			wasmParser.debug(false, false);
			wasmParser.parse();

			if (wasmParser.errorCount == 0 && !wasmLexer.failed) {
				bool init_found = false;
				std::list<decltype(wasmParser.root->children)::iterator> remove_inits;
				for (auto child_iter = wasmParser.root->begin(); child_iter != wasmParser.root->end(); ++child_iter)
					if ((*child_iter)->symbol == WASMTOK_INIT) {
						if (init_found)
							remove_inits.push_back(child_iter);
						else
							init_found = true;
					}
				if (!init_found)
					wasmParser.root->children.push_front(new ASTNode(wasmParser, WASMTOK_INIT));
				else
					for (auto child_iter: remove_inits)
						wasmParser.root->children.erase(child_iter);

				const std::vector<std::string> split_constraints = asm_node->constraints->size() < 2?
					std::vector<std::string>() :
					Util::split(asm_node->constraints->substr(1, asm_node->constraints->size() - 2), ",", false);

				// Count the number of "=r"'s at the beginning of the constraint list so we can skip over them.
				// For example, if the constraint list starts with "=r,=r,r,r", then we know that the input variables
				// start at $2 because there are two instances of "=r".
				int output_count = 0;
				auto constr_iter = split_constraints.begin(), end = split_constraints.end();
				for (; constr_iter != end && *constr_iter == "=r"; ++constr_iter)
					++output_count;

				VarMap map;

				// Scan the extractvalue instructions after the asm node and insert their defined variables into the
				// VarMap as output variables.
				int i = 0;
				auto copy = iter;
				for (++copy; copy != function.linearInstructions.end(); ++copy) {
					LLVMInstruction *inner_llvm = dynamic_cast<LLVMInstruction *>(copy->get());
					if (!inner_llvm || inner_llvm->node->nodeType() != NodeType::ExtractValue)
						break;

					ExtractValueNode *extract = dynamic_cast<ExtractValueNode *>(inner_llvm->node);
					if (*extract->aggregateType != *asm_node->returnType)
						break;

					if (extract->decimals.size() != 1) {
						error() << extract->debugExtra() << "\n";
						throw std::runtime_error("Invalid number of decimals in extractvalue node: " +
							std::to_string(extract->decimals.size()));
					}

					if (!extract->variable) {
						error() << extract->debugExtra() << "\n";
						throw std::runtime_error("Variable is null in extractvalue node");
					}

					const int decimal = extract->decimals.front();
					map.emplace(StringSet::intern("$" + std::to_string(decimal)), extract->variable);
					to_remove.push_back(*copy);
				}

				std::list<InstructionPtr> init_instructions;

				i = 0;
				for (; constr_iter != end && *constr_iter == "r"; ++constr_iter) {
					ConstantPtr constant = asm_node->constants[i];
					VariablePtr var;
					if (constant->value->isIntLike()) {
						var = function.newVariable(constant->type);
						init_instructions.push_back(std::make_shared<SetInstruction>(var, constant->value->intValue()));
					} else if (constant->value->valueType() == ValueType::Local) {
						var = dynamic_cast<LocalValue *>(constant->value.get())->variable;
					} else {
						throw std::runtime_error("Unhandled value type in asm constraints: " +
							std::to_string(static_cast<int>(constant->value->valueType())));
					}

					map.emplace(StringSet::intern("$" + std::to_string(i + output_count)), var);
					++i;
				}

				InstructionPtr last = function.comment(*iter, "LowerInlineAsm");
				to_remove.push_back(*iter);

				for (ASTNode *child: *wasmParser.root) {
					if (child->symbol == WASMTOK_INIT) {
						InstructionPtr comment = std::make_shared<Comment>("*init start");
						function.insertAfter(last, comment);
						last = comment;
						for (InstructionPtr &to_add: init_instructions) {
							function.insertAfter(last, to_add);
							last = to_add;
						}
						comment = std::make_shared<Comment>("*init end");
						function.insertAfter(last, comment);
						last = comment;
					} else if (WASMInstructionNode *wasm_instruction = dynamic_cast<WASMInstructionNode *>(child)) {
						InstructionPtr new_instruction = wasm_instruction->convert(function, map);
						function.insertAfter(last, new_instruction);
						last = new_instruction;
					}
				}
			}

			wasmParser.done();
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return count;
	}
}
