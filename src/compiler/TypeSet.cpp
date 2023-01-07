#include "compiler/BasicType.h"
#include "compiler/TypeSet.h"

#include <sstream>

namespace LL2W {
	bool TypeSet::anySigned(Program *program) const {
		for (const auto &type: *this)
			if (type->getSignedness(program) == Signedness::Signed)
				return true;
		return false;
	}

	bool TypeSet::anyUnsigned(Program *program) const {
		for (const auto &type: *this)
			if (type->getSignedness(program) == Signedness::Unsigned)
				return true;
		return false;
	}

	bool TypeSet::allSigned(Program *program) const {
		for (const auto &type: *this)
			if (type->getSignedness(program) != Signedness::Signed)
				return false;
		return true;
	}

	bool TypeSet::allUnsigned(Program *program) const {
		for (const auto &type: *this)
			if (type->getSignedness(program) != Signedness::Unsigned)
				return false;
		return true;
	}

	bool TypeSet::isMixed(Program *program) const {
		bool any_signed = false;
		bool any_unsigned = false;
		for (const auto &type: *this) {
			const auto signedness = type->getSignedness(program);
			if (signedness == Signedness::Signed) {
				if (any_unsigned)
					return true;
				any_signed = true;
			} else if (signedness == Signedness::Unsigned) {
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
			const auto signedness = type->getSignedness(program);
			if (signedness == Signedness::Signed) {
				if (out == Composition::UnsignedOnly)
					return Composition::Mixed;
				if (out == Composition::Empty)
					out = Composition::SignedOnly;
			} else if (signedness == Signedness::Unsigned) {
				if (out == Composition::SignedOnly)
					return Composition::Mixed;
				if (out == Composition::Empty)
					out = Composition::UnsignedOnly;
			}
		}
		return out;
	}

	Signedness TypeSet::getSignedness(Program *program) {
		const Composition composition = getComposition(program);
		if (composition == Composition::SignedOnly)
			return Signedness::Signed;
		if (composition == Composition::UnsignedOnly)
			return Signedness::Unsigned;
		if (composition == Composition::Mixed || composition == Composition::Empty)
			// throw std::runtime_error("TypeSet " + std::to_string(id) + " has mixed composition");
			return Signedness::Unknown;
		throw std::runtime_error("TypeSet " + std::to_string(id) + " has invalid composition " +
			std::to_string(static_cast<int>(composition)));
	}

	TypeSet::operator std::string() {
		std::ostringstream ss;
		ss << '!' << id << " = !{";
		bool first = true;
		for (const auto &type: *this) {
			if (first)
				first = false;
			else
				ss << ", ";
			if (type)
				ss << '!' << type->id;
			else
				ss << "null";
		}
		ss << '}';
		return ss.str();
	}
}
