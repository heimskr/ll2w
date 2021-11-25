#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "parser/ASTNode.h"
#include "parser/Enums.h"
#include "parser/StringSet.h"
#include "compiler/WhyInfo.h"
#include "util/Makeable.h"
#include "util/Util.h"

namespace LL2W {
	class StructNode;

	class Type;
	using TypePtr = std::shared_ptr<Type>;

	class Type {
		public:
			virtual TypeType typeType() const { return TypeType::None; }
			/** Returns an LLVM-style string representation of the type with ANSI styling. */
			virtual operator std::string() = 0;
			/** Returns an LLVM-style string representation of the type without ANSI styling. */
			virtual std::string toString() = 0;
			virtual ~Type() {}
			virtual TypePtr copy() const = 0;
			/** Returns the width of the type in bits. */
			virtual int width() const = 0;
			/** Returns the alignment of the type in bytes. */
			virtual int alignment() const = 0;
			virtual bool operator==(const Type &other) const { return typeType() == other.typeType(); }
			virtual bool operator!=(const Type &other) const { return !(*this == other); }
			bool isInt() const;
	};

	struct VoidType: public Type {
		TypeType typeType() const override { return TypeType::Void; }
		VoidType() {}
		operator std::string() override { return "void"; }
		std::string toString() override { return "void"; }
		TypePtr copy() const override { return std::make_shared<VoidType>(); }
		int width() const override { return 0; }
		int alignment() const override { return 1; }
	};

	struct IntType: public Type {
		TypeType typeType() const override { return TypeType::Int; }
		/** The width of the integer in bits. */
		int intWidth;
		IntType(int width_): intWidth(width_) {}
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<IntType>(intWidth); }
		int width() const override { return Util::upalign(intWidth, 8); }
		int alignment() const override { return Util::alignToPower(intWidth) / 8; }
		bool operator==(const Type &other) const override;
		static std::shared_ptr<IntType> make(int width) { return std::make_shared<IntType>(width); }
	};

	struct AggregateType: public Type {
		virtual TypePtr extractType(std::list<int> indices) const = 0;
		TypePtr extractType(const std::vector<int> &indices) const {
			return extractType(std::list<int>(indices.begin(), indices.end()));
		}
	};

	struct HasSubtype {
		TypePtr subtype;
		HasSubtype() = delete;
		HasSubtype(const TypePtr &subtype_): subtype(subtype_) {}
	};

	struct ArrayType: public AggregateType, public HasSubtype {
		TypeType typeType() const override { return TypeType::Array; }
		int count;
		ArrayType(int count_, TypePtr subtype_): HasSubtype(subtype_), count(count_) {}
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<ArrayType>(count, subtype->copy()); }
		int width() const override { return count * subtype->width(); }
		int alignment() const override { return subtype->alignment(); }
		TypePtr extractType(std::list<int>) const override { return subtype->copy(); }
		bool operator==(const Type &) const override;
	};

	struct VectorType: public ArrayType {
		TypeType typeType() const override { return TypeType::Vector; }
		using ArrayType::ArrayType;
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<VectorType>(count, subtype->copy()); }
		bool operator==(const Type &) const override;
	};

	struct FloatType: public Type {
		TypeType typeType() const override { return TypeType::Float; }
		enum class Type: int {Half, Float, Double, FP128, x86_FP80, PPC_FP128};
		FloatType::Type type;
		FloatType(FloatType::Type type_): type(type_) {}
		operator std::string() override;
		std::string toString() override;
		LL2W::TypePtr copy() const override { return std::make_shared<FloatType>(type); }
		static Type getType(const std::string &);
		int width() const override;
		int alignment() const override { return Util::alignToPower(width() / 8); }
		bool operator==(const LL2W::Type &) const override;
	};

	struct PointerType: public Type, public HasSubtype {
		TypeType typeType() const override { return TypeType::Pointer; }
		PointerType(TypePtr subtype_): HasSubtype(subtype_) {}
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<PointerType>(subtype->copy()); }
		int width() const override { return WhyInfo::pointerWidth * 8; }
		int alignment() const override { return WhyInfo::pointerWidth; }
		bool operator==(const Type &) const override;
		static std::shared_ptr<PointerType> make(TypePtr subtype) { return std::make_shared<PointerType>(subtype); }
	};

	class FunctionType: public Type {
		private:
			TypeType typeType() const override { return TypeType::Function; }
			std::string cached, cachedPlain;

		public:
			TypePtr returnType;
			std::vector<TypePtr> argumentTypes;
			bool ellipsis;
			FunctionType(const ASTNode *);
			FunctionType(TypePtr return_type, std::vector<TypePtr> &argument_types,
			bool ellipsis_ = false):
				returnType(return_type), argumentTypes(std::move(argument_types)), ellipsis(ellipsis_) {}
			void uncache() { cached.clear(); }
			operator std::string() override;
			std::string toString() override;
			TypePtr copy() const override;
			int width() const override { return WhyInfo::pointerWidth; }
			int alignment() const override;
			bool operator==(const Type &) const override;
			bool operator!=(const Type &) const override;
	};

	struct StructType: public AggregateType, public std::enable_shared_from_this<StructType> {
		bool padded = false;
		/** Map indices in the struct before padding to the corresponding indices after padding has been inserted.
		 *  If padded is false, this is empty. */
		std::map<int, int> paddingMap;
		std::shared_ptr<StructType> paddedChild;
		static std::unordered_map<std::string, std::shared_ptr<StructType>> knownStructs;
		TypeType typeType() const override { return TypeType::Struct; }
		const std::string *name;
		StructForm form = StructForm::Struct;
		StructShape shape = StructShape::Default;
		std::shared_ptr<StructNode> node;
		StructType(const std::string *name_, StructForm form_ = StructForm::Struct,
		           StructShape shape_ = StructShape::Default);
		StructType(std::shared_ptr<StructNode>);
		StructType(const StructNode *);
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override;
		int width() const override;
		int alignment() const override;
		TypePtr extractType(std::list<int> indices) const override;
		std::string barename() const;
		bool operator==(const Type &) const override;
		/** Assumes that each member in a struct has a width that's a multiple of 8. */
		std::shared_ptr<StructType> pad();
	};

	/** Global variables are specified without a type indicator. This means that when we encounter a global variable, we
	 *  have to defer its type resolution until everything is done parsing and use a temporary type in the meantime.
	 *  After that, we need to traverse the AST and replace all the temporary types with the known type of the global
	 *  variable. */
	struct GlobalTemporaryType: Type, Makeable<GlobalTemporaryType> {
		TypeType typeType() const override { return TypeType::GlobalTemporary; }
		const std::string *globalName;
		GlobalTemporaryType(const std::string *globalName_): globalName(globalName_) {}
		GlobalTemporaryType(const ASTNode *node): GlobalTemporaryType(StringSet::intern(node->extractName())) {}
		operator std::string() override { return "\e[1;4m@" + *globalName + "\e[0m"; }
		std::string toString() override { return "@" + *globalName; }
		TypePtr copy() const override { return std::make_shared<GlobalTemporaryType>(globalName); }
		int width() const override { throw std::runtime_error("Calling GlobalTemporaryType::width() is invalid"); }
		int alignment() const override;
		bool operator==(const Type &) const override;
	};

	/** During padded struct extraction, it's necessary to read one register from a register pack representing a struct.
	 *  This register may contain data from multiple members or from only a fraction of member, and as such has no
	 *  specific type. However, it's always one register in size. */
	struct OpaqueType: public Type {
		TypeType typeType() const override { return TypeType::Opaque; }
		OpaqueType() {}
		operator std::string() override { return "\e[1mopaque\e[22m"; }
		std::string toString() override { return "opaque"; }
		TypePtr copy() const override { return std::make_shared<OpaqueType>(); }
		int width() const override { return 64; }
		int alignment() const override { warn() << "Opaque alignment is unspecified!\n"; return 8; }
		bool operator==(const Type &type) const override { return dynamic_cast<const OpaqueType *>(&type) != nullptr; }
	};

	TypePtr getType(const ASTNode *);
	std::ostream & operator<<(std::ostream &os, Type &type);
}
