#pragma once

#include "compiler/BasicBlock.h"
#include "compiler/Function.h"
#include "compiler/Immediate.h"
#include "compiler/Variable.h"
#include "instruction/WhyInstruction.h"

namespace LL2W {
	template <typename T = Immediate>
	struct JType: public WhyInstruction {
		using ValueType = T;

		VariablePtr rs;
		T addr;
		bool link;
		bool needsTransformation = false;

		JType(VariablePtr rs_, T addr_, bool link_, int index_ = -1):
			WhyInstruction(index_), rs(std::move(rs_)), addr(std::move(addr_)), link(link_) {}

		ExtractionResult extract(bool force = false) override {
			if (extracted && !force)
				return {read.size(), 0};

			read.clear();
			written.clear();

			if (rs && !secretReads)
				read.insert(rs);

			extracted = true;
			return {read.size(), 0};
		}

		bool replaceRead(const VariablePtr &to_replace, const VariablePtr &new_var) override {
			if (rs->isAliasOf(*to_replace)) {
				rs = new_var;
				return true;
			}

			return false;
		}

		bool canReplaceRead(const VariablePtr &to_replace) const override {
			return rs->isAliasOf(*to_replace);
		}

		std::vector<const std::string *> getLabels() const override {
			if constexpr (std::is_same_v<T, Immediate>) {
				// TODO: will probably cause compilation failure if there are any subclasses with T != Immediate.
				if (std::holds_alternative<const std::string *>(addr))
					return {std::get<const std::string *>(addr)};
			}

			return {};
		}

		bool holdsLabels() const override {
			return std::is_same_v<T, Immediate>;
		}

		bool replaceLabel(const std::string *to_replace, const std::string *replace_with) override {
			if constexpr (std::is_same_v<T, Immediate>) {
				if (std::holds_alternative<const std::string *>(addr)) {
					const std::string * &label = std::get<const std::string *>(addr);
					if (label == to_replace) {
						label = replace_with;
					} else {
						Function &function = *parent.lock()->parent;
						if (*label == function.transformLabel(*to_replace))
							label = StringSet::intern(function.transformLabel(*replace_with));
					}
				}
			}

			return false;
		}

		bool operator==(const Instruction &other) const override {
			if (typeid(*this) != typeid(other))
				return false;
			const auto &other_j = dynamic_cast<const JType &>(other);
			return rs == other_j.rs && addr == other_j.addr && link == other_j.link &&
				needsTransformation == other_j.needsTransformation;
		}
	};
}
