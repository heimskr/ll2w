#include "compiler/BasicType.h"
#include "compiler/TypeSet.h"

namespace LL2W {
	bool TypeSet::anySigned() const {
		for (const auto &type: *this)
			if (type->isSigned())
				return true;
		return false;
	}

	bool TypeSet::anyUnsigned() const {
		for (const auto &type: *this)
			if (!type->isSigned())
				return true;
		return false;
	}

	bool TypeSet::allSigned() const {
		for (const auto &type: *this)
			if (!type->isSigned())
				return false;
		return true;
	}

	bool TypeSet::allUnsigned() const {
		for (const auto &type: *this)
			if (type->isSigned())
				return false;
		return true;
	}

	bool TypeSet::isMixed() const {
		bool any_signed = false;
		bool any_unsigned = false;
		for (const auto &type: *this) {
			if (type->isSigned()) {
				if (any_unsigned)
					return true;
				any_signed = true;
			} else {
				if (any_signed)
					return true;
				any_unsigned = true;
			}
		}
		return false;
	}

	TypeSet::Composition TypeSet::getComposition() const {
		Composition out = Composition::Empty;
		for (const auto &type: *this) {
			if (type->isSigned()) {
				if (out == Composition::UnsignedOnly)
					return Composition::Mixed;
				if (out == Composition::Empty)
					out = Composition::SignedOnly;
			} else {
				if (out == Composition::SignedOnly)
					return Composition::Mixed;
				if (out == Composition::Empty)
					out = Composition::UnsignedOnly;
			}
		}
		return out;
	}
}
