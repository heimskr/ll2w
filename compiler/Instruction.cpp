#include <iostream>

#include "compiler/Instruction.h"
#include "util/Util.h"

#define IFLV(x) if (const LocalValue *local_value = dynamic_cast<const LocalValue *>((x))) readname(local_value)
#define FORV(x...) for (const Value *value: {x})
#define CAST(t) const t *cast = dynamic_cast<const t *>(node)

namespace LL2W {
	bool Instruction::isTerminal() const {
		const NodeType type = node->nodeType();
		return type == NodeType::Ret || type == NodeType::Unreachable;
	}

	std::pair<char, char> Instruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		auto readname = [&](const LocalValue *lv) {
			read.push_back(parseLong(lv->name));
		};

		auto write = [&](const std::string *str) {
			if (str)
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

			case NodeType::Call:
			case NodeType::Invoke: {
				CAST(CallInvokeNode);
				write(cast->result);
				for (const Constant *constant: cast->constants)
					IFLV(constant->value);
				break;
			}

			case NodeType::Getelementptr: {
				CAST(GetelementptrNode);
				write(cast->result);
				read.push_back(parseLong(cast->ptrValue->name));
				for (auto [width, value, minrange, pvar]: cast->indices) {
					if (pvar)
						read.push_back(value);
				}
				break;
			}

			case NodeType::Ret: {
				CAST(RetNode);
				IFLV(cast->value);
				break;
			}

			case NodeType::Landingpad: {
				CAST(LandingpadNode);
				for (const LandingpadNode::Clause *clause: cast->clauses)
					IFLV(clause->value);
				break;
			}

			case NodeType::Conversion: {
				CAST(ConversionNode);
				write(cast->result);
				IFLV(cast->value);
				break;
			}

			case NodeType::BasicMath: {
				CAST(BasicMathNode);
				write(cast->result);
				IFLV(cast->left);
				IFLV(cast->right);
				break;
			}

			case NodeType::Phi: {
				CAST(PhiNode);
				write(cast->result);
				for (const std::pair<Value *, const std::string *> &pair: cast->pairs)
					IFLV(pair.first);
				break;
			}

			case NodeType::Div:
			case NodeType::Rem:
			case NodeType::Logic:
			case NodeType::Shr:
			case NodeType::FMath: {
				CAST(SimpleNode);
				write(cast->result);
				IFLV(cast->left);
				IFLV(cast->right);
				break;
			}

			case NodeType::ExtractValue: {
				CAST(ExtractValueNode);
				write(cast->result);
				IFLV(cast->aggregateValue);
				break;
			}

			case NodeType::InsertValue: {
				CAST(InsertValueNode);
				write(cast->result);
				IFLV(cast->aggregateValue);
				IFLV(cast->value);
				break;
			}

			case NodeType::Resume: {
				CAST(ResumeNode);
				IFLV(cast->value);
				break;
			}

			case NodeType::Unreachable: {
				break;
			}

			default:
				return {-1, -1};
		}

		return {read.size(), written.size()};
	}

	bool Instruction::operator<(const Instruction &other) const {
		return index < other.index;
	}

	bool Instruction::operator>(const Instruction &other) const {
		return index > other.index;
	}
}
