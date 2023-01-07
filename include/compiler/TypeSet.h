#pragma once

#include <memory>
#include <set>

#include "compiler/LLVMType.h"

namespace LL2W {
	struct TypeSet: std::set<std::shared_ptr<LLVMType>>, LLVMType {
		enum class Composition {Invalid, Empty, SignedOnly, UnsignedOnly, Mixed};

		using std::set<std::shared_ptr<LLVMType>>::set;

		bool anySigned(Program *) const;
		bool anyUnsigned(Program *) const;
		bool allSigned(Program *) const;
		bool allUnsigned(Program *) const;
		bool isMixed(Program *) const;
		Composition getComposition(Program *) const;

		Signedness getSignedness(Program *) override;
		operator std::string() override;
	};
}
