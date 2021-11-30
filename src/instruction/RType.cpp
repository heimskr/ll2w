#include "compiler/Variable.h"
#include "instruction/RType.h"

namespace LL2W {
	RType::RType(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rt_, std::shared_ptr<Variable> rd_,
	int index_):
		WhyInstruction(index_), rs(rs_), rt(rt_), rd(rd_) {}

	std::string RType::operDebug(const char *oper) const {
		return std::string(*rs) + " \e[2m" + std::string(oper) + "\e[0m " + std::string(*rt) + " \e[2m->\e[22m " +
			std::string(*rd);
	}

	std::string RType::operString(const char *oper) const {
		return rs->toString() + " " + std::string(oper) + " " + rt->toString() + " -> " + rd->toString();
	}

	ExtractionResult RType::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		if (rs && !secretReads)
			read.insert(rs);
		if (rt && !secretReads)
			read.insert(rt);
		if (rd && !secretWrites)
			written.insert(rd);

		return {read.size(), written.size()};
	}

	bool RType::replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) {
		bool changed = false;

		if (rs && rs->isAliasOf(*to_replace)) {
			rs = new_var;
			changed = true;
		}

		if (rt && rt->isAliasOf(*to_replace)) {
			rt = new_var;
			changed = true;
		}

		return changed;
	}

	bool RType::canReplaceRead(std::shared_ptr<Variable> to_replace) const {
		return rs->isAliasOf(*to_replace) || rt->isAliasOf(*to_replace);
	}

	bool RType::replaceWritten(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var) {
		if (rd->isAliasOf(*to_replace)) {
			rd = new_var;
			return true;
		}

		return false;
	}

	bool RType::canReplaceWritten(std::shared_ptr<Variable> to_replace) const {
		return rd->isAliasOf(*to_replace);
	}
}
