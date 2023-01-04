#pragma once

#include <optional>

#include "compiler/Immediate.h"
#include "compiler/Variable.h"
#include "parser/Values.h"
#include "instruction/WhyInstruction.h"

namespace LL2W {
	class IType: public WhyInstruction {
		protected:
			std::string operDebug(const char *oper) const;
			std::string operString(const char *oper) const;

		public:
			using IVariablePtr = VariablePtr IType::*;

			ValuePtr originalValue;
			VariablePtr rs;
			VariablePtr rd;
			Immediate imm;

			IType(VariablePtr rs_, Immediate imm_, VariablePtr rd_, int index_ = -1);

			IType * setOriginalValue(const ValuePtr &);

			ExtractionResult extract(bool force = false) override;
			bool replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) override;
			bool canReplaceRead(const VariablePtr &to_replace) const override;
			bool replaceWritten(const VariablePtr &to_replace, const VariablePtr &new_var) override;
			bool canReplaceWritten(const VariablePtr &to_replace) const override;
			bool operator==(const Instruction &other) const override;
			std::vector<IVariablePtr> findDifferences(const IType &other) const;

			virtual Role rsRole() const { return Role::Source; }
			virtual Role rdRole() const { return Role::Destination; }
			bool typeMismatch() const override;
	};
}
