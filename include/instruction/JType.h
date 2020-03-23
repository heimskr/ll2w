#ifndef INSTRUCTION_JTYPE_H_
#define INSTRUCTION_JTYPE_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	template <typename T = int>
	struct JType: public WhyInstruction {
		std::shared_ptr<Variable> rs;
		T addr;
		bool link;

		JType(std::shared_ptr<Variable> rs_, T addr_, bool link_, int index_ = -1):
			WhyInstruction(index_), rs(rs_), addr(addr_), link(link_) {}

		ExtractionResult extract(bool force = false) override {
		if (extracted && !force)
			return {read.size(), 0};

		read.clear();
		written.clear();

		if (rs)
			read.insert(rs);

		extracted = true;
		return {read.size(), 0};
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
