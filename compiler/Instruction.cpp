#include <iostream>

#include "compiler/Instruction.h"
#include "util/Util.h"

#define IFLV(x) if (const LocalValue *local_value = dynamic_cast<const LocalValue *>((x))) readname(local_value)
#define FORV(x...) for (const Value *value: {x})

namespace LL2W {
	std::pair<char, char> Instruction::extract() {
		read.clear();
		written.clear();

		auto readname = [&](const LocalValue *lv) {
			read.push_back(parseLong(lv->name));
		};

		auto write = [&](const std::string *str) {
			written.push_back(parseLong(str));
		};

		switch (node->nodeType()) {
			case NodeType::Select: {
				const SelectNode *select = dynamic_cast<const SelectNode *>(node);
				FORV(select->firstValue, select->secondValue) {
					IFLV(value);
				}
				written.push_back(parseLong(select->result));
				break;
			}

			case NodeType::Alloca: {
				const AllocaNode *alloca = dynamic_cast<const AllocaNode *>(node);
				write(alloca->result);
				IFLV(alloca->numelementsValue);
				break;
			}

			case NodeType::Store: {
				const StoreNode *store = dynamic_cast<const StoreNode *>(node);
				FORV(store->value, store->constant->value)
					IFLV(value);
				break;
			}

			case NodeType::Load: {
				const LoadNode *load = dynamic_cast<const LoadNode *>(node);
				write(load->result);
				IFLV(load->constant->value);
				break;
			}

			case NodeType::Icmp: {
				const IcmpNode *icmp = dynamic_cast<const IcmpNode *>(node);
				write(icmp->result);
				FORV(icmp->value1, icmp->value2)
					IFLV(value);
				break;
			}

			default:
				return {-1, -1};
				// std::cout << "\e[2m[\e[0;33m!\e[0;2m]\e[0m Unknown instruction type: "
				//           << static_cast<int>(node->nodeType());
		}

		return {read.size(), written.size()};
	}
}

#undef IFLV
#undef FORV
