#include "instruction/JType.h"

namespace LL2W {
	JType::JType(std::shared_ptr<Variable> rs_, T addr_, bool link_, int index_):
		WhyInstruction(index_), rs(rs_), addr(addr_), link(link_) {}

	ExtractionResult JType::extract(bool force) {
		if (extracted && !force)
			return {read.size(), 0};

		read.clear();
		written.clear();

		if (rs)
			read.insert(rs);

		extracted = true;
		return {read.size(), 0};
	}

	bool JType::replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) {
		if (rs == to_replace) {
			rs = new_var;
			return true;
		}

		return false;
	}
}
