#include <iostream>

#include "compiler/Instruction.h"
#include "util/Util.h"

namespace LL2W {
	std::pair<char, char> Instruction::extract() {
		switch (node->nodeType()) {
			case NodeType::Select: {
				const SelectNode *select = dynamic_cast<const SelectNode *>(node);
				int readCount = 0;
				for (const Value *value: {select->firstValue, select->secondValue}) {
					if (const LocalValue *local_value = dynamic_cast<const LocalValue *>(value)) {
						readCount++;
						read.push_back(parseLong(local_value->name));
					}
				}
				written.push_back(parseLong(select->result));
				return {readCount, 1};
			}

			case NodeType::Alloca: {
				const AllocaNode *alloca = dynamic_cast<const AllocaNode *>(node);
				written.push_back(parseLong(alloca->result));
				if (const LocalValue *local_value = dynamic_cast<const LocalValue *>(alloca->numelementsValue)) {
					read.push_back(parseLong(local_value->name));
					return {1, 1};
				}
				return {0, 1};
			}

			default:
				std::cout << "\e[2m[\e[0;33m!\e[0;2m]\e[0m Unknown instruction type: "
				          << static_cast<int>(node->nodeType());
		}

		return {0, 0};
	}
}