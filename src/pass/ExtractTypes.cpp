#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "pass/ExtractTypes.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	static DbgIntrinsicNode * getDbg(const InstructionPtr &instruction) {
		auto llvm = std::dynamic_pointer_cast<LLVMInstruction>(instruction);
		return llvm? dynamic_cast<DbgIntrinsicNode *>(llvm->node) : nullptr;
	}

	static bool isIntbang(const std::string &str) {
		if (str.size() < 2 || str.front() != '!')
			return false;
		for (size_t i = 1; i < str.size(); ++i)
			if (!std::isdigit(str[i]))
				return false;
		return true;
	}

	void extractTypes(Function &function) {
		Timer timer("ExtractTypes");

		std::list<InstructionPtr> to_remove;

		// First, attempt to glean information from calls to @llvm.dbg.value intrinsics.
		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto *dbg = getDbg(instruction)) {
				to_remove.push_back(instruction);
				if (dbg->type == DbgIntrinsicNode::Type::Value) {
					const std::string &first = *dbg->firstMetadata->lexerInfo;
					if (!isIntbang(first))
						throw std::invalid_argument("Not an intbang: \"" + first + '"');

					const int bang = dbg->firstMetadata->atoi();
					if (!function.parent.localVariables.contains(bang))
						continue;

					ValuePtr value = dbg->constant->convert()->value;

					if (!value->isLocal())
						continue;

					VariablePtr var = std::dynamic_pointer_cast<LocalValue>(value)->getVariable(function);

					if (!var->type)
						throw std::runtime_error("Variable " + std::string(*var) + " has no type");
					
					if (!var->type->isInt())
						continue;

					const auto &local = function.parent.localVariables.at(bang);
					if (!function.parent.basicTypes.contains(local.type)) {
						// Probably something like !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !x, size: 64).
						continue;
					}

					const TypeSet &types = function.parent.basicTypes.at(local.type);
					const auto composition = types.getComposition();
					auto &signedness = std::dynamic_pointer_cast<IntType>(var->type)->signedness;

					switch (composition) {
						case TypeSet::Composition::Mixed:
							warn() << *var << " is Mixed at " << dbg->location << '\n';
							break;
						case TypeSet::Composition::SignedOnly:
							signedness = IntType::Signedness::Signed;
							break;
						case TypeSet::Composition::UnsignedOnly:
							signedness = IntType::Signedness::Unsigned;
							break;
						case TypeSet::Composition::Empty:
							warn() << *var << " is Empty at " << dbg->location << '\n';
							break;
						default:
							throw std::logic_error("Invalid composition: " +
								std::to_string(static_cast<int>(composition)));
					}
				}
			}
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
