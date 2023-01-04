#include "compiler/Variable.h"
#include "instruction/ThreeSourcesRType.h"

namespace LL2W {
	ExtractionResult ThreeSourcesRType::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		if (!secretReads) {
			if (rs)
				read.insert(rs);
			if (rt)
				read.insert(rt);
			if (rd)
				read.insert(rd);
		}

		return {read.size(), written.size()};
	}

	bool ThreeSourcesRType::replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) {
		bool out = false;

		if (rs && rs->isAliasOf(*to_replace)) {
			rs = new_var;
			out = true;
		}

		if (rt && rt->isAliasOf(*to_replace)) {
			rt = new_var;
			out = true;
		}

		if (rd && rd->isAliasOf(*to_replace)) {
			rd = new_var;
			return true;
		}

		return out;
	}

	bool ThreeSourcesRType::canReplaceRead(const VariablePtr &to_replace) const {
		return (rs && rs->isAliasOf(*to_replace)) || (rt && rt->isAliasOf(*to_replace)) ||
		       (rd && rd->isAliasOf(*to_replace));
	}

	bool ThreeSourcesRType::replaceWritten(const VariablePtr &, const VariablePtr &) {
		return false;
	}

	bool ThreeSourcesRType::canReplaceWritten(const VariablePtr &) const {
		return false;
	}
}
