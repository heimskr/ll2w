#include <sstream>
#include <stdexcept>

#include "ASTNode.h"
#include "Types.h"

namespace LL2W {
	IntType::operator std::string() {
		return "i" + std::to_string(width);
	}

	FloatType::operator std::string() {
		switch (type) {
			case FloatType::Type::Half: return "half";
			case FloatType::Type::Double: return "double";
			case FloatType::Type::FP128: return "fp128";
			case FloatType::Type::x86_FP80: return "x86_fp80";
			case FloatType::Type::PPC_FP128: return "ppc_fp128";
			default: throw std::runtime_error("Unrecognized float type: " + std::to_string(static_cast<int>(type)));
		}
	}

	FunctionType::operator std::string() {
		if (!cached.empty())
			return cached;

		std::stringstream out;

		Type *return_type = getType(node->children.at(0));
		out << std::string(*return_type) << " (";
		delete return_type;

		if (node->children.size() == 3) {
			ASTNode *list = node->children.at(2);
			for (size_t i = 0, l = list->children.size(); i < l; ++i) {
				if (i)
					out << ", ";
				Type *arg_type = getType(list->children.at(i));
				out << std::string(*arg_type);
				delete arg_type;
			}

			if (node->children.at(1))
				out << ", ...";
		} else if (node->children.at(1)) {
			out << "...";
		}

		out << ") *";
		return cached = out.str();
	}

	Type * getType(ASTNode *node) {
		switch (node->symbol) {
			
		}
	}
}
