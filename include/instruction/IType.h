#ifndef INSTRUCTION_ITYPE_H_
#define INSTRUCTION_ITYPE_H_

#include "compiler/Immediate.h"
#include "compiler/Variable.h"
#include "instruction/WhyInstruction.h"

namespace LL2W {
	template <typename T = Immediate>
	class IType: public WhyInstruction {
		protected:
			std::string operDebug(const char *oper) const {
				return std::string(*rs) + " \e[2m" + std::string(oper) + "\e[0m " + colorize(imm) + " \e[2m->\e[0m " +
					std::string(*rd);
			}

			std::string operString(const char *oper) const {
				return rs->toString() + " " + std::string(oper) + " " + LL2W::toString(imm) + " -> " + rd->toString();
			}

		public:
			using ValueType = T;

			std::shared_ptr<Variable> rs, rd;
			T imm;

			IType(std::shared_ptr<Variable> rs_, T imm_, std::shared_ptr<Variable> rd_, int index_ = -1):
				WhyInstruction(index_), rs(rs_), rd(rd_), imm(imm_) {}

			ExtractionResult extract(bool force = false) override {
				if (extracted && !force)
					return {read.size(), written.size()};

				read.clear();
				written.clear();

				if (rs)
					read.insert(rs);
				if (rd)
					written.insert(rd);

				extracted = true;
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

#endif
