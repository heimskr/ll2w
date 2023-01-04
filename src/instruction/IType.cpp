#include "instruction/IType.h"

namespace LL2W {
	std::string IType::operDebug(const char *oper) const {
		return std::string(*rs) + " \e[2m" + std::string(oper) + "\e[22m " + colorize(imm, *rs) +
			" \e[2m->\e[22m " + std::string(*rd);
	}

	std::string IType::operString(const char *oper) const {
		return rs->toString() + " " + std::string(oper) + " " + LL2W::toString(imm, *rs) + " -> " +
			rd->toString();
	}

	IType::IType(VariablePtr rs_, Immediate imm_, VariablePtr rd_, int index_):
		WhyInstruction(index_), rs(std::move(rs_)), rd(std::move(rd_)), imm(std::move(imm_)) {}

	IType * IType::setOriginalValue(const ValuePtr &value) {
		originalValue = value;
		return this;
	}

	ExtractionResult IType::extract(bool force) {
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

	bool IType::replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) {
		if (rs->isAliasOf(*to_replace)) {
			rs = new_var;
			return true;
		}

		return false;
	}

	bool IType::canReplaceRead(const VariablePtr &to_replace) const {
		return rs->isAliasOf(*to_replace);
	}

	bool IType::replaceWritten(const VariablePtr &to_replace, const VariablePtr &new_var) {
		if (rd->isAliasOf(*to_replace)) {
			rd = new_var;
			return true;
		}

		return false;
	}

	bool IType::canReplaceWritten(const VariablePtr &to_replace) const {
		return rd->isAliasOf(*to_replace);
	}

	bool IType::operator==(const Instruction &other) const {
		if (typeid(*this) != typeid(other))
			return false;
		const auto &other_i = dynamic_cast<const IType &>(other);
		return rs == other_i.rs && imm == other_i.imm && rd == other_i.rd &&
			originalValue == other_i.originalValue;
	}

	std::vector<IType::IVariablePtr> IType::findDifferences(const IType &other) const {
		std::vector<IVariablePtr> out;
		out.reserve(2);
		if (*rs != *other.rs)
			out.push_back(&IType::rs);
		if (*rd != *other.rd)
			out.push_back(&IType::rd);
		return out;
	}

	bool IType::typeMismatch() const {
		if (rs && rd)
			return rs->getSignedness() != rd->getSignedness();
		return false;
	}
}