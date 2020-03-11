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
	}
	
	ParAttrs::ParAttrs(const ASTNode &node) {
		for (const ASTNode *child: node) {
			if (child->symbol == TOK_DEREF) {
				dereferenceable = atoi(child->at(0)->lexerInfo->c_str());
				orNull = *child->lexerInfo == "dereferenceable_or_null";
			} else if (child->symbol == TOK_ALIGN) {
				align = atoi(child->at(0)->lexerInfo->c_str());
			} else if (child->symbol == TOK_BYVAL) {
				attributes.insert(ParAttr::Byval);
				if (child->size() == 1)
					byvalType = getType(child->at(0));
			} else {
				for (const std::pair<ParAttr, std::string> &pair: parattr_map) {
					if (*child->lexerInfo == pair.second) {
						attributes.insert(pair.first);
						break;
					}
				}
			}
		}
	}

	ParAttrs::~ParAttrs() {
		if (byvalType)
			delete byvalType;
	}

	ParAttrs & ParAttrs::operator=(const ParAttrs &other) {
		if (byvalType) {
			delete byvalType;
			byvalType = nullptr;
		}

		attributes = other.attributes;
		if (other.byvalType)
			byvalType = other.byvalType->copy();
		align = other.align;
		dereferenceable = other.dereferenceable;
		orNull = other.orNull;
		return *this;
	}

	ParAttrs::operator std::string() const {
		std::stringstream out;
		std::string str = out.str();
		for (ParAttr attribute: attributes) {
			if (attribute != ParAttr::Byval || !byvalType)
				out << parattr_map.at(attribute) << " ";
		}
		if (byvalType)
			out << "byval(" << std::string(*byvalType) << ") ";
		if (dereferenceable != -1)
			out << "dereferenceable" << (orNull? "_or_null" : "") << "(" << dereferenceable << ") ";
		if (align != -1)
			out << "align " << align << " ";
		if (!str.empty())
			str.pop_back(); // Remove the extra space at the end
		return str;
	}
}