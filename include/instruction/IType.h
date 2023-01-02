#pragma once

#include <optional>

#include "compiler/Immediate.h"
#include "compiler/Variable.h"
#include "parser/Values.h"
#include "instruction/WhyInstruction.h"

namespace LL2W {
	template <typename T = Immediate>
	class IType: public WhyInstruction {
		protected:
			std::string operDebug(const char *oper) const {
				return std::string(*rs) + " \e[2m" + std::string(oper) + "\e[22m " + colorize(imm, *rs) +
					" \e[2m->\e[22m " + std::string(*rd);
			}

			std::string operString(const char *oper) const {
				return rs->toString() + " " + std::string(oper) + " " + LL2W::toString(imm, *rs) + " -> " +
					rd->toString();
			}

		public:
			using ValueType = T;

			ValuePtr originalValue;
			VariablePtr rs, rd;
			T imm;

			IType(std::shared_ptr<Variable> rs_, T imm_, std::shared_ptr<Variable> rd_, int index_ = -1):
				WhyInstruction(index_), rs(std::move(rs_)), rd(std::move(rd_)), imm(std::move(imm_)) {}

			IType * setOriginalValue(const ValuePtr &value) {
				originalValue = value;
				return this;
			}

			ExtractionResult extract(bool force = false) override {
				if (extracted && !force)
					return {read.size(), written.size()};

				read.clear();
				written.clear();
				extracted = true;

				if (rs && !secretReads)
					read.insert(rs);
				if (rd && !secretWrites)
					written.insert(rd);

				return {read.size(), written.size()};
			}

			bool replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) override {
				if (rs->isAliasOf(*to_replace)) {
					rs = new_var;
					return true;
				}

				return false;
			}

			bool canReplaceRead(const VariablePtr &to_replace) const override {
				return rs->isAliasOf(*to_replace);
			}

			bool replaceWritten(const VariablePtr &to_replace, const VariablePtr &new_var) override {
				if (rd->isAliasOf(*to_replace)) {
					rd = new_var;
					return true;
				}

				return false;
			}

			bool canReplaceWritten(const VariablePtr &to_replace) const override {
				return rd->isAliasOf(*to_replace);
			}
	};
}
