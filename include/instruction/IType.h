#ifndef INSTRUCTION_ITYPE_H_
#define INSTRUCTION_ITYPE_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	template <typename T = int>
	struct IType: public WhyInstruction {
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
			if (rs == to_replace) {
				rs = new_var;
				return true;
			}

			return false;
		}
	};
}

#endif
