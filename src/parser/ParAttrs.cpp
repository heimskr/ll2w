#include <sstream>

#include "parser/ASTNode.h"
#include "parser/ParAttrs.h"
#include "parser/Types.h"
#include "parser/Lexer.h"

namespace LL2W {
	ParAttrs::ParAttrs() {}

	ParAttrs::ParAttrs(const ParAttrs &source) {
		attributes = source.attributes;
		if (source.byvalType)
			byvalType = source.byvalType->copy();
		align = source.align;
		dereferenceable = source.dereferenceable;
		orNull = source.orNull;
		signext = source.signext;
	}
	
	ParAttrs::ParAttrs(const ASTNode &node) {
		for (const ASTNode *child: node) {
			if (child->symbol == LLVMTOK_DEREF) {
				dereferenceable = atoi(child->at(0)->lexerInfo->c_str());
				orNull = *child->lexerInfo == "dereferenceable_or_null";
			} else if (child->symbol == LLVMTOK_ALIGN) {
				align = atoi(child->at(0)->lexerInfo->c_str());
			} else
				for (const std::pair<const ParAttr, std::string> &pair: parattr_map)
					if (*child->lexerInfo == pair.second) {
						attributes.insert(pair.first);
						if (pair.first == ParAttr::Signext)
							signext = true;
						break;
					}
		}
	}

	ParAttrs & ParAttrs::operator=(const ParAttrs &other) {
		if (this == &other)
			return *this;

		attributes = other.attributes;
		byvalType = other.byvalType? other.byvalType->copy() : nullptr;
		align = other.align;
		dereferenceable = other.dereferenceable;
		orNull = other.orNull;
		signext = other.signext;
		return *this;
	}

	ParAttrs::operator std::string() const {
		std::stringstream out;
		for (ParAttr attribute: attributes)
			if (attribute != ParAttr::Byval || !byvalType)
				out << parattr_map.at(attribute) << " ";
		if (byvalType)
			out << "byval(" << std::string(*byvalType) << ") ";
		if (dereferenceable != -1)
			out << "dereferenceable" << (orNull? "_or_null" : "") << "(" << dereferenceable << ") ";
		if (align != -1)
			out << "align " << align << " ";
		std::string str = out.str();
		if (!str.empty())
			str.pop_back(); // Remove the extra space at the end
		return str;
	}
}