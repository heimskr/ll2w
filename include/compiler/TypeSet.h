#pragma once

#include <memory>
#include <set>

namespace LL2W {
	struct BasicType;

	struct TypeSet: std::set<std::shared_ptr<BasicType>> {
		enum class Composition {Invalid, Empty, SignedOnly, UnsignedOnly, Mixed};
		using std::set<std::shared_ptr<BasicType>>::set;
		bool anySigned() const;
		bool anyUnsigned() const;
		bool allSigned() const;
		bool allUnsigned() const;
		bool isMixed() const;
		Composition getComposition() const;
	};
}
