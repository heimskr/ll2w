#include <iostream>

#include "compiler/Function.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Variable.h"
#include "parser/Nodes.h"
#include "util/Util.h"

#define IFLV(x, t) if (const LocalValue *local_value = dynamic_cast<const LocalValue *>((x))) readname(local_value, (t))
#define FORV(x...) for (const Value *value: {x})
#define CAST(t) const t *cast = dynamic_cast<const t *>(node)

namespace LL2W {
	bool LLVMInstruction::isTerminal() const {
		const NodeType type = node->nodeType();
		return type == NodeType::Ret || type == NodeType::Unreachable;
	}

	ExtractionResult LLVMInstruction::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		std::unordered_set<int> read_ids, written_ids;

		auto readname = [&](const LocalValue *lv, const Type *type) {
			read.insert(parent->parent->getVariable(parseLong(lv->name), type));
		};

		auto write = [&](const std::string *str, const Type *type) {
			if (str)
				written.insert(parent->parent->getVariable(parseLong(str), type, parent));
		};

		switch (node->nodeType()) {
			case NodeType::Select: {
				CAST(SelectNode);
				write(cast->result, cast->firstType);
				IFLV(cast->firstValue, cast->firstType);
				IFLV(cast->secondValue, cast->secondType);
				break;
			}

			case NodeType::Alloca: {
				CAST(AllocaNode);
				PointerType *ptr = new PointerType(cast->type->copy());
				write(cast->result, ptr);
				delete ptr;
				IFLV(cast->numelementsValue, cast->numelementsType);
				break;
			}

			case NodeType::Store: {
				CAST(StoreNode);
				IFLV(cast->value, cast->type);
				IFLV(cast->constant->value, cast->constant->type);
				break;
			}

			case NodeType::Load: {
				CAST(LoadNode);
				write(cast->result, cast->type);
				IFLV(cast->constant->value, cast->constant->type);
				break;
			}

			case NodeType::Icmp: {
				CAST(IcmpNode);
				write(cast->result, cast->type);
				FORV(cast->value1, cast->value2)
					IFLV(value, cast->type);
				break;
			}

			case NodeType::BrUncond: {
				// Unconditional branches don't read anything; their PVARs represent labels, not registers.
				break;
			}

			case NodeType::BrCond: {
				CAST(BrCondNode);
				IFLV(cast->condition, new IntType(1));
				break;
			}

			case NodeType::Call:
			case NodeType::Invoke: {
				CAST(CallInvokeNode);
				write(cast->result, cast->returnType);
				for (const Constant *constant: cast->constants)
					IFLV(constant->value, constant->type);
				break;
			}

			case NodeType::Getelementptr: {
				CAST(GetelementptrNode);
				write(cast->result, cast->type);
				int id = parseLong(cast->ptrValue->name);
				if (read_ids.count(id) == 0) {
					read.insert(parent->parent->getVariable(id, cast->ptrType));
					read_ids.insert(id);
				}
				for (auto [width, value, minrange, pvar]: cast->indices) {
					// Because we're assuming that these variables have already been defined earlier in the function,
					// we can get them from the Function that contains this Instruction.
					if (pvar)
						read.insert(parent->parent->getVariable(value));
				}
				break;
			}

			case NodeType::Ret: {
				CAST(RetNode);
				IFLV(cast->value, cast->type);
				break;
			}

			case NodeType::Landingpad: {
				CAST(LandingpadNode);
				for (const LandingpadNode::Clause *clause: cast->clauses)
					IFLV(clause->value, clause->type);
				break;
			}

			case NodeType::Conversion: {
				CAST(ConversionNode);
				write(cast->result, cast->to);
				IFLV(cast->value, cast->from);
				break;
			}

			case NodeType::BasicMath: {
				CAST(BasicMathNode);
				write(cast->result, cast->type);
				FORV(cast->left, cast->right)
					IFLV(value, cast->type);
				break;
			}

			case NodeType::Phi: {
				CAST(PhiNode);
				write(cast->result, cast->type);
				for (const std::pair<Value *, const std::string *> &pair: cast->pairs)
					IFLV(pair.first, cast->type);
				break;
			}

			case NodeType::Div:
			case NodeType::Rem:
			case NodeType::Logic:
			case NodeType::Shr:
			case NodeType::FMath: {
				CAST(SimpleNode);
				write(cast->result, cast->type);
				FORV(cast->left, cast->right)
					IFLV(value, cast->type);
				break;
			}

			case NodeType::ExtractValue: {
				CAST(ExtractValueNode);
				write(cast->result, cast->aggregateType->extractType(cast->decimals));
				IFLV(cast->aggregateValue, cast->aggregateType);
				break;
			}

			case NodeType::InsertValue: {
				CAST(InsertValueNode);
				write(cast->result, cast->aggregateType);
				IFLV(cast->aggregateValue, cast->aggregateType);
				IFLV(cast->value, cast->type);
				break;
			}

			case NodeType::Resume: {
				CAST(ResumeNode);
				IFLV(cast->value, cast->type);
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

	std::string LLVMInstruction::debugExtra() {
		return node->debugExtra();
	}
}