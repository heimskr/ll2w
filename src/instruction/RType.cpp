#include "instruction/RType.h"

namespace LL2W {
	RType::RType(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rt_, std::shared_ptr<Variable> rd_,
	int index_):
		WhyInstruction(index_), rs(rs_), rt(rt_), rd(rd_) {}

	ExtractionResult RType::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();

		if (rs)
			read.insert(rs);
		if (rt)
			read.insert(rt);
		if (rd)
			written.insert(rd);

		extracted = true;
		return {read.size(), written.size()};
	}
}