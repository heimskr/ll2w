#pragma once

#include "instruction/WhyInstruction.h"
#include "parser/Enums.h"

namespace LL2W {
	class RType: public WhyInstruction {
		protected:
			using VariablePtr = std::shared_ptr<Variable>;
			std::string operDebug(const char *) const;
			std::string operString(const char *) const;

		public:
			using RVariablePtr = VariablePtr RType::*;
			VariablePtr rs;
			VariablePtr rt;
			VariablePtr rd;

			RType(VariablePtr rs, VariablePtr rt, VariablePtr rd);

			ExtractionResult extract(bool force = false) override;
			bool replaceRead(const VariablePtr &, const VariablePtr &) override;
			bool canReplaceRead(const VariablePtr &) const override;
			bool replaceWritten(const VariablePtr &, const VariablePtr &) override;
			bool canReplaceWritten(const VariablePtr &) const override;
			bool operator==(const Instruction &) const override;

			std::vector<RVariablePtr> findDifferences(const RType &other) const;

			virtual Role rsRole() const { return Role::Source; }
			virtual Role rtRole() const { return Role::Source; }
			virtual Role rdRole() const { return Role::Destination; }

			bool typeMismatch() const override;
	};
}
