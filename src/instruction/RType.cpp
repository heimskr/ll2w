#include "compiler/Variable.h"
#include "instruction/RType.h"

namespace LL2W {
	RType::RType(VariablePtr rs, VariablePtr rt, VariablePtr rd):
		rs(std::move(rs)), rt(std::move(rt)), rd(std::move(rd)) {}

	std::string RType::operDebug(const char *oper) const {
		return std::string(*rs) + " \e[2m" + std::string(oper) + "\e[22m " + std::string(*rt) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string RType::operString(const char *oper) const {
		return rs->toString() + " " + std::string(oper) + " " + rt->toString() + " -> " + rd->toString();
	}

	ExtractionResult RType::extract(bool force) {
		if (extracted && !force) {
			return {read.size(), written.size()};
		}

		read.clear();
		written.clear();
		extracted = true;

		if (rs && !secretReads) {
			read.insert(rs);
		}

		if (rt && !secretReads) {
			read.insert(rt);
		}

		if (rd && !secretWrites) {
			written.insert(rd);
		}

		return {read.size(), written.size()};
	}

	bool RType::replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) {
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

	bool RType::canReplaceRead(const VariablePtr &to_replace) const {
		return (rs && rs->isAliasOf(*to_replace)) || (rt && rt->isAliasOf(*to_replace));
	}

	bool RType::replaceWritten(const VariablePtr &to_replace, const VariablePtr &new_var) {
		if (rd && rd->isAliasOf(*to_replace)) {
			rd = new_var;
			return true;
		}

		return false;
	}

	bool RType::canReplaceWritten(const VariablePtr &to_replace) const {
		return rd && rd->isAliasOf(*to_replace);
	}

	bool RType::operator==(const Instruction &other) const {
		if (this == &other) {
			return true;
		}

		if (typeid(*this) != typeid(other)) {
			return false;
		}

		const auto &other_r = dynamic_cast<const RType &>(other);
		return rs == other_r.rs && rt == other_r.rt && rd == other_r.rd;
	}

	std::vector<RType::RVariablePtr> RType::findDifferences(const RType &other) const {
		std::vector<RVariablePtr> out;
		out.reserve(3);
		if (*rs != *other.rs) {
			out.push_back(&RType::rs);
		}
		if (*rt != *other.rt) {
			out.push_back(&RType::rt);
		}
		if (*rd != *other.rd) {
			out.push_back(&RType::rd);
		}
		return out;
	}

	bool RType::typeMismatch() const {
		if (rs && rt) {
			return !rs->compatible(*rt);
		}

		if (rs && rd) {
			// const bool out = rs->getSignedness() != rd->getSignedness();
			const bool out = !rs->compatible(*rd);
			if (out) {
				info() << *this << "\n    rs[" << char(rs->getSignedness()) << "], rt[" << char(rd->getSignedness()) << "]\n";
			}
			return out;
		}

		return false;
	}
}
