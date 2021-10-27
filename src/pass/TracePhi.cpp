#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "graph/Graph.h"
#include "pass/TracePhi.h"

namespace LL2W::Passes {
	void tracePhi(Function &function) {
		Graph dependencies;
		for (InstructionPtr &instruction: function.linearInstructions) {
			// If it isn't an LLVMInstruction whose node is a PhiNode, continue scanning.
			LLVMInstruction *llvm_instruction = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (!llvm_instruction || llvm_instruction->node->nodeType() != NodeType::Phi)
				continue;
			const PhiNode *phi_node = dynamic_cast<const PhiNode *>(llvm_instruction->node);
			if (!phi_node)
				throw std::runtime_error("phi_node is null in Function::coalescePhi");

			if (!dependencies.hasLabel(*phi_node->result))
				dependencies.addNode(*phi_node->result);
			
			for (const auto &[value, block_label]: phi_node->pairs) {
				if (value->valueType() == ValueType::Local) {
					auto *local = dynamic_cast<LocalValue *>(value.get());
					const std::string &name = *local->name;
					if (!dependencies.hasLabel(name))
						dependencies.addNode(name);
					dependencies.link(name, *phi_node->result);
				}
			}
		}

		dependencies.renderTo("dependencies.png");
		std::list<Graph> components = dependencies.components();
		components.sort([](const Graph &left, const Graph &right) { return left.size() < right.size(); });
		size_t sum = 0;
		size_t i = 0;
		for (Graph &graph: components) {
			std::cerr << ++i << ": size = " << graph.size() << '\n';
			for (const auto &[from, to]: graph.bridges())
				std::cerr << "    " << from << " -> " << to << '\n';
			sum += graph.size();
			graph.renderTo("component_" + std::to_string(i) + ".png");
			std::cerr << '\n';
		}
		std::cerr << "Sum: " << sum << " (vs. " << dependencies.size() << ")\n";
	}
}
