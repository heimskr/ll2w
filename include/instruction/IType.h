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
			std::shared_ptr<Variable> rs, rd;
			T imm;

			IType(std::shared_ptr<Variable> rs_, T imm_, std::shared_ptr<Variable> rd_, int index_ = -1):
				WhyInstruction(index_), rs(rs_), rd(rd_), imm(imm_) {}

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

			bool replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) override {
				if (rs->isAliasOf(*to_replace)) {
					rs = new_var;
					return true;
				}

				return false;
			}

			bool canReplaceRead(std::shared_ptr<Variable> to_replace) const override {
				return rs->isAliasOf(*to_replace);
			}

			bool replaceWritten(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) override {
				if (rd->isAliasOf(*to_replace)) {
					rd = new_var;
					return true;
				}

				return false;
			}

			bool canReplaceWritten(std::shared_ptr<Variable> to_replace) const override {
				return rd->isAliasOf(*to_replace);
			}
	};
}
