#include <iostream>

#include "compiler/Instruction.h"
#include "util/Util.h"

#define IFLV(x) if (const LocalValue *local_value = dynamic_cast<const LocalValue *>((x))) readname(local_value)
#define FORV(x...) for (const Value *value: {x})
#define CAST(t) const t *cast = dynamic_cast<const t *>(node)

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
				CAST(SelectNode);
				write(cast->result);
				FORV(cast->firstValue, cast->secondValue)
					IFLV(value);
				break;
			}

			case NodeType::Alloca: {
				CAST(AllocaNode);
				write(cast->result);
				IFLV(cast->numelementsValue);
				break;
			}

			case NodeType::Store: {
				CAST(StoreNode);
				FORV(cast->value, cast->constant->value)
					IFLV(value);
				break;
			}

			case NodeType::Load: {
				CAST(LoadNode);
				write(cast->result);
				IFLV(cast->constant->value);
				break;
			}

			case NodeType::Icmp: {
				CAST(IcmpNode);
				write(cast->result);
				FORV(cast->value1, cast->value2)
					IFLV(value);
				break;
			}

			case NodeType::BrUncond: {
				// Unconditional branches don't read anything; their PVARs represent labels, not registers.
				break;
			}

			case NodeType::BrCond: {
				CAST(BrCondNode);
				IFLV(cast->condition);
				break;
			}

			default:
				// std::cout << "\e[2m[\e[0;33m!\e[0;2m]\e[0m Unknown instruction type: "
				//           << static_cast<int>(node->nodeType());
				return {-1, -1};
		}

		return {read.size(), written.size()};
	}
}

#undef IFLV
#undef FORV
