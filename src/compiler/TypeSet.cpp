#include "compiler/BasicType.h"
#include "compiler/TypeSet.h"

namespace LL2W {
	bool TypeSet::anySigned(Program *program) const {
		for (const auto &type: *this)
			if (type->isSigned(program))
				return true;
		return false;
	}

	bool TypeSet::anyUnsigned(Program *program) const {
		for (const auto &type: *this)
			if (!type->isSigned(program))
				return true;
		return false;
	}

	bool TypeSet::allSigned(Program *program) const {
		for (const auto &type: *this)
			if (!type->isSigned(program))
				return false;
		return true;
	}

	bool TypeSet::allUnsigned(Program *program) const {
		for (const auto &type: *this)
			if (type->isSigned(program))
				return false;
		return true;
	}

	bool TypeSet::isMixed(Program *program) const {
		bool any_signed = false;
		bool any_unsigned = false;
		for (const auto &type: *this) {
			if (type->isSigned(program)) {
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

	TypeSet::Composition TypeSet::getComposition(Program *program) const {
		Composition out = Composition::Empty;
		for (const auto &type: *this) {
			if (type->isSigned(program)) {
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

	bool TypeSet::isSigned(Program *program) {
		const Composition composition = getComposition(program);
		if (composition == Composition::SignedOnly)
			return true;
		if (composition == Composition::UnsignedOnly)
			return false;
		if (composition == Composition::Mixed)
			throw std::runtime_error("TypeSet " + std::to_string(id) + " has mixed composition");
		throw std::runtime_error("TypeSet " + std::to_string(id) + " has invalid composition " +
			std::to_string(static_cast<int>(composition)));
	}
}
