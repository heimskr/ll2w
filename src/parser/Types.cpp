#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "options.h"
#include "compiler/PaddedStructs.h"
#include "exception/SignednessSharingError.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/Types.h"
#include "parser/StructNode.h"

namespace LL2W {

	std::string whyString(const TypePtr &type) {
		return type == nullptr? "n" : type->whyString();
	}

	bool Type::isInt() const {
		return typeType() == TypeType::Int;
	}

	bool Type::isInt(int bit_width) const {
		return typeType() == TypeType::Int && dynamic_cast<const IntType *>(this)->intWidth == bit_width;
	}

	bool Type::isPointer() const {
		return typeType() == TypeType::Pointer;
	}

	bool Type::isVoid() const {
		return typeType() == TypeType::Void;
	}

	std::vector<TypePtr> Type::copyMany(const std::vector<TypePtr> &types) {
		std::vector<TypePtr> out;
		out.reserve(types.size());
		for (const auto &type: types)
			out.push_back(type->copy());
		return out;
	}

	IntType::operator std::string() {
		return std::string("\e[33m") + static_cast<char>(signedness) + std::to_string(intWidth) + "\e[0m";
	}

	std::string IntType::toString() {
		return static_cast<char>(signedness) + std::to_string(intWidth);
	}

	bool IntType::operator==(const Type &other) const {
		return this == &other ||
			(other.typeType() == TypeType::Int && dynamic_cast<const IntType &>(other).intWidth == intWidth);
	}

	std::shared_ptr<IntType> IntType::make(int width, Signedness signedness) {
		return std::make_shared<IntType>(width, signedness);
	}

	std::shared_ptr<IntType> IntType::make(int width, bool is_signed) {
		return std::make_shared<IntType>(width, is_signed? Signedness::Signed : Signedness::Unsigned);
	}

	std::string IntType::whyString() const {
		std::string out;
		if (signedness != Signedness::Unknown)
			out += static_cast<char>(signedness);
		switch (intWidth) {
			case  8: out += 'c'; break;
			case 16: out += 's'; break;
			case 32: out += 'i'; break;
			case 64: out += 'l'; break;
			default: out += std::to_string(intWidth);
		}
		return out;
	}

	bool IntType::isSimilarTo(const Type &other) const {
		const auto *other_int = dynamic_cast<const IntType *>(&other);
		return other_int != nullptr && other_int->intWidth == intWidth;
	}

	bool IntType::shareSignedness(const TypePtr &other) {
		if (auto other_int = std::dynamic_pointer_cast<IntType>(other->unwrapAll())) {
			if (other_int->signedness != Signedness::Unknown) {
				if (signedness != Signedness::Unknown) {
					if (signedness != other_int->signedness)
						throw SignednessSharingError("Signednesses don't match in IntType::shareSignedness",
							std::dynamic_pointer_cast<IntType>(shared_from_this()), other_int);
					return false;
				}

				setSignedness(other_int->getSignedness());
				return true;
			}

			if (signedness != Signedness::Unknown) {
				other_int->setSignedness(getSignedness());
				return true;
			}
		}

		return false;
	}

	bool IntType::setSignedness(Signedness new_signedness) {
		const bool out = signedness != new_signedness;
		signedness = new_signedness;
		signednessBacktrace = Util::getBacktrace();
		return out;
	}

	std::shared_ptr<IntType> IntType::invertedCopy() const {
		Signedness new_signedness = Signedness::Unknown;
		if (signedness == Signedness::Signed)
			new_signedness = Signedness::Unsigned;
		else if (signedness == Signedness::Unsigned)
			new_signedness = Signedness::Signed;
		return std::make_shared<IntType>(intWidth, new_signedness);
	}

	ArrayType::operator std::string() {
		return "\e[2m[\e[0m" + std::to_string(count) + " \e[2mx\e[0m " + std::string(*subtype) + "\e[2m]\e[0m";
	}

	std::string ArrayType::toString() {
		return "[" + std::to_string(count) + " x " + subtype->toString() + "]";
	}

	bool ArrayType::operator==(const Type &other) const {
		if (this == &other)
			return true;
		if (other.typeType() != TypeType::Array)
			return false;
		if (const ArrayType *otherArray = dynamic_cast<const ArrayType *>(&other))
			return count == otherArray->count && *otherArray->subtype == *subtype;
		return false;
	}

	std::string ArrayType::whyString() const {
		return subtype->whyString() + '*';
	}

	VectorType::operator std::string() {
		return "\e[2m<\e[0m" + std::to_string(count) + " \e[2mx\e[0m " + std::string(*subtype) + "\e[2m>\e[0m";
	}

	std::string VectorType::toString() {
		return "<" + std::to_string(count) + " x " + subtype->toString() + ">";
	}

	bool VectorType::operator==(const Type &other) const {
		if (this == &other)
			return true;
		if (other.typeType() != TypeType::Vector)
			return false;
		if (const VectorType *otherVector = dynamic_cast<const VectorType *>(&other))
			return count == otherVector->count && *otherVector->subtype == *subtype;
		return false;
	}

	std::string VectorType::whyString() const {
		return subtype->whyString() + '<' + std::to_string(count) + '>';
	}

	FloatType::operator std::string() {
		switch (type) {
			case FloatType::Type::Half: return "half";
			case FloatType::Type::Float: return "float";
			case FloatType::Type::Double: return "double";
			case FloatType::Type::FP128: return "fp128";
			case FloatType::Type::x86_FP80: return "x86_fp80";
			case FloatType::Type::PPC_FP128: return "ppc_fp128";
			default: throw std::runtime_error("Unrecognized float type: " + std::to_string(static_cast<int>(type)));
		}
	}

	std::string FloatType::toString() {
		return std::string(*this);
	}

	FloatType::Type FloatType::getType(const std::string &str) {
		if (str == "half") return FloatType::Type::Half;
		else if (str == "float") return FloatType::Type::Float;
		else if (str == "double") return FloatType::Type::Double;
		else if (str == "fp128") return FloatType::Type::FP128;
		else if (str == "x86_fp80") return FloatType::Type::x86_FP80;
		else if (str == "ppc_fp128") return FloatType::Type::PPC_FP128;
		throw std::invalid_argument("Unknown float type: " + str);
	}

	int FloatType::width() const {
		switch (type) {
			case FloatType::Type::Half:   return WhyInfo::halfFloatWidth;
			case FloatType::Type::Float:  return WhyInfo::floatWidth;
			case FloatType::Type::Double: return WhyInfo::doubleWidth;
			default: return WhyInfo::doubleWidth;
		}
	}

	bool FloatType::operator==(const LL2W::Type &other) const {
		return this == &other ||
			(other.typeType() == TypeType::Float && dynamic_cast<const FloatType &>(other).type == type);
	}

	PointerType::operator std::string() {
		return std::string(*subtype) + "\e[1;2m*\e[0m";
	}

	std::string PointerType::toString() {
		return subtype->toString() + "*";
	}

	bool PointerType::operator==(const Type &other) const {
		return this == &other ||
			(other.typeType() == TypeType::Pointer && *dynamic_cast<const PointerType &>(other).subtype == *subtype);
	}

	std::string PointerType::whyString() const {
		return subtype->whyString() + '*';
	}

	bool PointerType::shareSignedness(const TypePtr &other) {
		return unwrapAll()->shareSignedness(other->unwrapAll());
	}

	FunctionType::FunctionType(const ASTNode *node) {
		returnType = getType(node->at(0));
		if (node->children.size() == 3 || (1 < node->size() && node->at(1)->symbol == LLVM_TYPE_LIST)) {
			ASTNode *list = node->at(1);
			argumentTypes.reserve(list->children.size());
			for (ASTNode *child: *list)
				argumentTypes.push_back(getType(child));
		}

		ellipsis = node->size() == 3 || (1 < node->size() && node->at(1)->symbol == LLVMTOK_ELLIPSIS);
	}

	FunctionType::operator std::string() {
		if (!cached.empty())
			return cached;

		std::stringstream out;
		out << std::string(*returnType) << " (";

		if (!argumentTypes.empty()) {
			for (size_t i = 0, l = argumentTypes.size(); i < l; ++i) {
				if (i)
					out << ", ";
				out << std::string(*argumentTypes.at(i));
			}

			if (ellipsis)
				out << ", ...";
		} else if (ellipsis) {
			out << "...";
		}

		out << ") *";
		return cached = out.str();
	}

	std::string FunctionType::toString() {
		if (!cachedPlain.empty())
			return cachedPlain;

		std::stringstream out;
		out << returnType->toString() << " (";

		if (!argumentTypes.empty()) {
			for (size_t i = 0, l = argumentTypes.size(); i < l; ++i) {
				if (i)
					out << ", ";
				out << argumentTypes.at(i)->toString();
			}

			if (ellipsis)
				out << ", ...";
		} else if (ellipsis) {
			out << "...";
		}

		out << ") *";
		return cachedPlain = out.str();
	}

	TypePtr FunctionType::copy() const {
		std::vector<TypePtr> argument_types {};
		for (TypePtr argument_type: argumentTypes)
			argument_types.push_back(argument_type->copy());
		return std::make_shared<FunctionType>(returnType->copy(), argument_types);
	}

	int FunctionType::alignment() const {
		warn() << "Function alignment is unspecified!\n";
		return WhyInfo::pointerWidth;
	}

	bool FunctionType::operator==(const Type &other) const {
		if (this == &other)
			return true;
		if (other.typeType() != TypeType::Function)
			return false;
		const FunctionType &otherFunction = dynamic_cast<const FunctionType &>(other);
		if (ellipsis != otherFunction.ellipsis || argumentTypes.size() != otherFunction.argumentTypes.size())
			return false;
		if (*returnType != *otherFunction.returnType)
			return false;
		for (size_t i = 0, size = argumentTypes.size(); i < size; ++i) {
			if (*argumentTypes[i] != *otherFunction.argumentTypes[i])
				return false;
		}
		return true;
	}

	bool FunctionType::operator!=(const Type &other) const {
		if (other.typeType() != TypeType::Function)
			return true;
		const FunctionType &otherFunction = dynamic_cast<const FunctionType &>(other);
		if (ellipsis != otherFunction.ellipsis || argumentTypes.size() != otherFunction.argumentTypes.size())
			return true;
		if (*returnType != *otherFunction.returnType)
			return true;
		for (size_t i = 0, size = argumentTypes.size(); i < size; ++i) {
			if (*argumentTypes[i] != *otherFunction.argumentTypes[i])
				return true;
		}
		return false;
	}

	std::unordered_map<std::string, std::shared_ptr<StructType>> StructType::knownStructs = {};

	StructType::StructType(const std::string *name_, StructForm form_, StructShape shape_):
		name(name_), form(form_), shape(shape_) {}

	StructType::StructType(std::shared_ptr<StructNode> node_):
		name(node_->name), form(node_->form), shape(node_->shape), node(node_) {}

	StructType::StructType(const StructNode *node_): StructType(std::shared_ptr<StructNode>(node_->copy())) {}

	StructType::operator std::string() {
		if (*name == "[anon]" && node)
			return node->typeString();
		if (name->at(1) == '"')
			return "\e[32m%\e[33m" + name->substr(1) + "\e[39m";
		return "\e[32m" + *name + "\e[39m";
	}

	std::string StructType::toString() {
		if (*name == "[anon]" && node)
			return node->typeStringPlain();
		if (name->at(1) == '"')
			return "%" + name->substr(1);
		return *name;
	}

	TypePtr StructType::copy() const {
		auto out = node? std::make_shared<StructType>(node) : std::make_shared<StructType>(name, form, shape);
		out->padded = padded;
		out->paddingMap = paddingMap;
		out->paddedChild = paddedChild;
		return out;
	}

	int StructType::width() const {
		int out = 0;
		if (!node) {
			// This is likely a named struct rather than a literal struct.
			return knownStructs.at(barename())->width();
		}

#ifdef STRUCT_PAD_CUSTOM
		return PaddedStructs::getOffset(*this, node->types.size());
#elif defined(STRUCT_PAD_X86)
		int largest = 0;
		for (const TypePtr &type: node->types) {
			const int width = type->width();
			if (width == 0)
				continue;
			out += width + ((width - (out % width)) % width);
			if (largest < width)
				largest = width;
		}
		if (largest != 0 && out % largest != 0)
			out += largest - (out % largest);
#else
		for (const TypePtr &type: node->types)
			out += type->width();
#endif
		return out;
	}

	int StructType::alignment() const {
		if (!node) {
			// This is likely a named struct rather than a literal struct.
			return knownStructs.at(barename())->alignment();
		}

		int largest = 0;
		for (const TypePtr &type: node->types) {
			const int subalignment = type->alignment();
			if (largest < subalignment)
				largest = subalignment;
		}
		return largest;
	}

	TypePtr StructType::extractType(std::list<int> indices) const {
		TypePtr type = node->types.at(indices.front())->copy();
		if (indices.size() == 1)
			return type;

		std::shared_ptr<AggregateType> aggregate = std::dynamic_pointer_cast<AggregateType>(type);
		if (!aggregate)
			throw std::runtime_error("Expected an AggregateType in StructType::extractType");

		indices.pop_front();
		type = aggregate->extractType(indices);

		std::cout << "Returning " << std::string(*type) << "\n";
		return type;
	}

	std::string StructType::barename() const {
		const std::string out = name->front() == '%'? name->substr(1) : *name;
		return out.front() == '"'? out.substr(1, out.size() - 2) : out;
	}

	bool StructType::operator==(const Type &other) const {
		if (this == &other)
			return true;
		// TODO: is this correct?
		if (other.typeType() != TypeType::Struct)
			return false;
		const StructType &otherstruct = dynamic_cast<const StructType &>(other);
		if (form != otherstruct.form || shape != otherstruct.shape)
			return false;
		if ((name && name != otherstruct.name) || (!name && otherstruct.name))
			return false;
		if (node) {
			if (!otherstruct.node || node->types.size() != otherstruct.node->types.size())
				return false;
			for (size_t i = 0, max = node->types.size(); i < max; ++i)
				if (*node->types[i] != *otherstruct.node->types[i])
					return false;
		}
		return true;
	}

	std::shared_ptr<StructType> StructType::pad() {
		if (padded)
			return std::dynamic_pointer_cast<StructType>(shared_from_this());

		if (paddedChild)
			return paddedChild;

		auto out = std::make_shared<StructType>(
			*name == "[anon]"? name : StringSet::intern(*name + "$padded"), form, StructShape::Default);

		out->node = std::make_shared<StructNode>(StructShape::Packed);

		int largest = 1, current_width = 0, padding_items_added = 0;
		for (TypePtr &subtype: node->types)
			largest = std::max(largest, subtype->width());

		for (size_t i = 0; i < node->types.size(); ++i) {
			const bool is_last = i == node->types.size() - 1;
			TypePtr &subtype = node->types[i];
			const int type_width = subtype->width();
			current_width += type_width;
			const int next_width = is_last? largest : node->types[i + 1]->width();
			if (subtype->typeType() == TypeType::Struct)
				out->node->types.push_back(dynamic_cast<StructType *>(subtype.get())->pad());
			else
				out->node->types.push_back(subtype->copy());
			out->paddingMap.emplace(i, i + padding_items_added);
			if (next_width) {
				int remaining = (next_width - current_width % next_width) % next_width;
				while (0 < remaining) {
					out->node->types.push_back(IntType::make(8, false));
					++padding_items_added;
					remaining -= 8;
					current_width += 8;
				}
			}
		}

		out->padded = true;
		paddedChild = out;
		return out;
	}

	int GlobalTemporaryType::alignment() const {
		throw std::runtime_error("Calling GlobalTemporaryType::alignment() is invalid");
	}

	bool GlobalTemporaryType::operator==(const Type &other) const {
		return this == &other || (other.typeType() == TypeType::GlobalTemporary &&
		                          dynamic_cast<const GlobalTemporaryType &>(other).globalName == globalName);
	}

	TypePtr getType(const ASTNode *node) {
		if (!node)
			throw std::runtime_error("node is null in getType");

		switch (node->symbol) {
			case LLVM_FUNCTIONTYPE: return std::make_shared<FunctionType>(node);
			case LLVMTOK_INTTYPE:   return std::make_shared<IntType>(atoi(node->lexerInfo->substr(1).c_str()));
			case LLVMTOK_FLOATTYPE: return std::make_shared<FloatType>(FloatType::getType(*node->lexerInfo));
			case LLVM_POINTERTYPE:  return std::make_shared<PointerType>(getType(node->at(0)));
			case LLVMTOK_VOID:      return std::make_shared<VoidType>();
			case LLVMTOK_STRUCTVAR: return std::make_shared<StructType>(node->lexerInfo, StructForm::Struct);
			case LLVMTOK_CLASSVAR:  return std::make_shared<StructType>(node->lexerInfo, StructForm::Class);
			case LLVMTOK_UNIONVAR:  return std::make_shared<StructType>(node->lexerInfo, StructForm::Union);
			case LLVM_STRUCTDEF:    return std::make_shared<StructType>(dynamic_cast<const StructNode *>(node));
			case LLVMTOK_GVAR:      return std::make_shared<GlobalTemporaryType>(node);
			case LLVM_ARRAYTYPE:
				return std::make_shared<ArrayType>(atoi(node->at(0)->lexerInfo->c_str()),getType(node->at(1)));
			case LLVM_VECTORTYPE:
				return std::make_shared<VectorType>(atoi(node->at(0)->lexerInfo->c_str()),getType(node->at(1)));
			default:
				throw std::invalid_argument("Couldn't create Type from a node with symbol " +
				                            std::string(llvmParser.getName(node->symbol)) + " (" +
				                            std::to_string(node->symbol) + ")");
		}
	}

	std::ostream & operator<<(std::ostream &os, Type &type) {
		return os << std::string(type);
	}
}
