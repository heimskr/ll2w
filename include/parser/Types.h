#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "parser/ASTNode.h"
#include "parser/Enums.h"
#include "parser/StringSet.h"
#include "compiler/WhyInfo.h"
#include "util/Makeable.h"
#include "util/Util.h"

namespace llvm {
	class StructType;
	class Type;
}

namespace LL2W {
	class StructNode;

	class Type;
	using TypePtr = std::shared_ptr<Type>;
	using TypeCPtr = std::shared_ptr<const Type>;

	std::string whyString(const TypePtr &);

	class Type: public std::enable_shared_from_this<Type> {
		public:
			virtual TypeType typeType() const { return TypeType::None; }
			/** Returns an LLVM-style string representation of the type with ANSI styling. */
			virtual operator std::string() = 0;
			/** Returns an LLVM-style string representation of the type without ANSI styling. */
			virtual std::string toString() = 0;
			virtual ~Type() {}
			virtual TypePtr copy() const = 0;
			/** Returns the width of the type in bits. */
			virtual ssize_t width() const = 0;
			/** Returns the alignment of the type in bytes. */
			virtual int alignment() const = 0;
			virtual bool operator==(const Type &other) const { return typeType() == other.typeType(); }
			virtual bool operator!=(const Type &other) const { return !(*this == other); }
			bool isInt() const;
			bool isInt(int bit_width) const;
			bool isPointer() const;
			bool isVoid() const;
			/** Returns a Why type string without braces. */
			virtual std::string whyString() const = 0;
			virtual TypePtr unwrap() { return shared_from_this(); }
			virtual TypeCPtr unwrap() const { return shared_from_this(); }
			virtual TypePtr unwrapAll() { return shared_from_this(); }
			virtual TypeCPtr unwrapAll() const { return shared_from_this(); }
			virtual bool shareSignedness(const TypePtr &) { return false; }
			static std::vector<TypePtr> copyMany(const std::vector<TypePtr> &);
			virtual bool compatible(const Type &) const { return true; }
			virtual Signedness getSignedness() const { return Signedness::Unknown; }
			/** Returns whether the signedness changed. */
			virtual bool setSignedness(Signedness) { return false; }

			static TypePtr fromLLVM(const llvm::Type &);
	};

	struct VoidType: Type {
		TypeType typeType() const override { return TypeType::Void; }
		VoidType() = default;
		operator std::string() override { return "void"; }
		std::string toString() override { return "void"; }
		TypePtr copy() const override { return std::make_shared<VoidType>(); }
		ssize_t width() const override { return 0; }
		int alignment() const override { return 1; }
		static std::shared_ptr<VoidType> make() { return std::make_shared<VoidType>(); }
		std::string whyString() const override { return "v"; }
	};

	struct AnyType: Type {
		TypeType typeType() const override { return TypeType::Any; }
		AnyType() = default;
		operator std::string() override { return "any"; }
		std::string toString() override { return "any"; }
		TypePtr copy() const override { return std::make_shared<AnyType>(); }
		ssize_t width() const override { return 64; }
		int alignment() const override { return 8; }
		static std::shared_ptr<AnyType> make() { return std::make_shared<AnyType>(); }
		std::string whyString() const override { return "v"; }
	};

	struct IntType: Type {
		TypeType typeType() const override { return TypeType::Int; }
		/** The width of the integer in bits. */
		ssize_t bitWidth;
		IntType(ssize_t width_, Signedness signedness_ = Signedness::Unknown):
			bitWidth(width_), signedness(signedness_) {}
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<IntType>(bitWidth, signedness); }
		ssize_t width() const override { return Util::upalign(bitWidth, 8); }
		int alignment() const override { return static_cast<int>(Util::alignToPower(bitWidth) / 8); }
		bool operator==(const Type &other) const override;
		static std::shared_ptr<IntType> make(ssize_t width, Signedness signedness = Signedness::Unknown);
		static std::shared_ptr<IntType> make(ssize_t width, bool is_signed);
		std::string whyString() const override;
		/** Returns whether the given Type is an IntType with the same width but not necessarily the same signedness. */
		bool isSimilarTo(const Type &) const;
		/** If the other type is an IntType and has no signedness, this function copies this IntType's signedness to it.
		 *  Otherwise, if the other type is an IntType and does have a signedness and this type doesn't, this function
		 *  copies the other type's signedness to this IntType. If the other type is an IntType and has a defined but
		 *  different signedness, this function throws std::runtime_error. */
		bool shareSignedness(const TypePtr &) override;
		Signedness getSignedness() const override { return signedness; }
		bool setSignedness(Signedness) override;
		const auto & getSignednessBacktrace() const { return signednessBacktrace; }
		/** Returns a copy with the opposite signedness. */
		std::shared_ptr<IntType> invertedCopy() const;
		bool compatible(const Type &) const override;

		private:
			Signedness signedness = Signedness::Unknown;
			std::vector<std::string> signednessBacktrace;
	};

	struct AggregateType: Type {
		virtual TypePtr extractType(std::list<int> indices) const = 0;
		TypePtr extractType(const std::vector<int> &indices) const {
			return extractType(std::list<int>(indices.begin(), indices.end()));
		}
	};

	struct HasSubtype {
		TypePtr subtype;
		HasSubtype() = delete;
		HasSubtype(TypePtr subtype_): subtype(std::move(subtype_)) {}
	};

	struct ArrayType: AggregateType, HasSubtype, Makeable<ArrayType> {
		TypeType typeType() const override { return TypeType::Array; }
		ssize_t count;
		ArrayType(ssize_t count_, TypePtr subtype_): HasSubtype(subtype_), count(count_) {}
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<ArrayType>(count, subtype->copy()); }
		ssize_t width() const override { return count * subtype->width(); }
		int alignment() const override { return subtype->alignment(); }
		TypePtr extractType(std::list<int>) const override { return subtype->copy(); }
		bool operator==(const Type &) const override;
		std::string whyString() const override;
		TypePtr unwrap() override { return subtype; }
		TypeCPtr unwrap() const override { return subtype; }
		TypePtr unwrapAll() override { return subtype->unwrapAll(); }
		TypeCPtr unwrapAll() const override { return subtype->unwrapAll(); }
	};

	struct VectorType: ArrayType {
		TypeType typeType() const override { return TypeType::Vector; }
		using ArrayType::ArrayType;
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<VectorType>(count, subtype->copy()); }
		bool operator==(const Type &) const override;
		std::string whyString() const override;
	};

	struct FloatType: Type, Makeable<FloatType> {
		TypeType typeType() const override { return TypeType::Float; }
		enum class Type: int {Half, Float, Double, FP128, x86_FP80, PPC_FP128};
		FloatType::Type type;
		FloatType(FloatType::Type type_): type(type_) {}
		operator std::string() override;
		std::string toString() override;
		LL2W::TypePtr copy() const override { return std::make_shared<FloatType>(type); }
		static Type getType(const std::string &);
		ssize_t width() const override;
		int alignment() const override { return Util::alignToPower(width() / 8); }
		bool operator==(const LL2W::Type &) const override;
		std::string whyString() const override { return "F"; }
	};

	struct PointerType: Type, HasSubtype {
		TypeType typeType() const override { return TypeType::Pointer; }
		PointerType(TypePtr subtype_): HasSubtype(std::move(subtype_)) {}
		operator std::string() override;
		std::string toString() override;
		TypePtr copy() const override { return std::make_shared<PointerType>(subtype->copy()); }
		ssize_t width() const override { return WhyInfo::pointerWidth * 8; }
		int alignment() const override { return WhyInfo::pointerWidth; }
		bool operator==(const Type &) const override;
		static std::shared_ptr<PointerType> make(TypePtr subtype) { return std::make_shared<PointerType>(subtype); }
		std::string whyString() const override;
		TypePtr unwrap() override { return subtype; }
		TypeCPtr unwrap() const override { return subtype; }
		TypePtr unwrapAll() override { return subtype->unwrapAll(); }
		TypeCPtr unwrapAll() const override { return subtype->unwrapAll(); }
		bool shareSignedness(const TypePtr &) override;
		bool compatible(const Type &) const override;
		std::shared_ptr<PointerType> invertedCopy() const;
		Signedness getSignedness() const override;
		bool setSignedness(Signedness) override;

		static std::shared_ptr<PointerType> getOpaque();
	};

	class FunctionType: public Type, public Makeable<FunctionType> {
		private:
			TypeType typeType() const override { return TypeType::Function; }
			std::string cached, cachedPlain;

		public:
			TypePtr returnType;
			std::vector<TypePtr> argumentTypes;
			bool ellipsis;
			FunctionType(const ASTNode *);
			FunctionType(TypePtr return_type, std::vector<TypePtr> argument_types, bool ellipsis = false):
				returnType(return_type), argumentTypes(std::move(argument_types)), ellipsis(ellipsis) {}
			void uncache() { cached.clear(); }
			operator std::string() override;
			std::string toString() override;
			TypePtr copy() const override;
			ssize_t width() const override { return WhyInfo::pointerWidth; }
			int alignment() const override;
			bool operator==(const Type &) const override;
			bool operator!=(const Type &) const override;
			std::string whyString() const override { return "v*"; }
	};

	struct StructType: AggregateType, Makeable<StructType> {
		public:
			bool padded = false;
			/** Map indices in the struct before padding to the corresponding indices after padding has been inserted.
			 *  If padded is false, this is empty. */
			std::map<int, int> paddingMap;
			std::shared_ptr<StructType> paddedChild;
			static std::unordered_map<std::string, std::shared_ptr<StructType>> knownStructs;
			TypeType typeType() const override { return TypeType::Struct; }
			std::string name;
			StructForm form = StructForm::Struct;
			StructShape shape = StructShape::Default;
			std::shared_ptr<StructNode> node;
			std::optional<std::vector<TypePtr>> types;

			StructType(std::string_view name, StructForm = StructForm::Struct, StructShape = StructShape::Default);
			StructType(std::shared_ptr<StructNode>);
			StructType(const StructNode *);
			StructType(const llvm::StructType &);

			operator std::string() override;
			std::string toString() override;
			TypePtr copy() const override;
			ssize_t width() const override;
			int alignment() const override;
			TypePtr extractType(std::list<int> indices) const override;
			std::string barename() const;
			bool operator==(const Type &) const override;
			/** Assumes that each member in a struct has a width that's a multiple of 8. */
			std::shared_ptr<StructType> pad();
			std::string whyString() const override { return "v"; }

		private:
			static StructForm getForm(const llvm::StructType &);
			static StructShape getShape(const llvm::StructType &);
			static std::vector<TypePtr> getTypes(const llvm::StructType &);
			std::string typeString() const;
			std::string typeStringPlain() const;
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
		ssize_t width() const override { return 64; }
		int alignment() const override;
		bool operator==(const Type &) const override;
		std::string whyString() const override { return "G"; }
	};

	/** During padded struct extraction, it's necessary to read one register from a register pack representing a struct.
	 *  This register may contain data from multiple members or from only a fraction of member, and as such has no
	 *  specific type. However, it's always one register in size. */
	struct OpaqueType: Type {
		TypeType typeType() const override { return TypeType::Opaque; }
		OpaqueType() {}
		operator std::string() override { return "\e[1mopaque\e[22m"; }
		std::string toString() override { return "opaque"; }
		TypePtr copy() const override { return std::make_shared<OpaqueType>(); }
		ssize_t width() const override { return 64; }
		int alignment() const override { warn() << "Opaque alignment is unspecified!\n"; return 8; }
		bool operator==(const Type &type) const override { return dynamic_cast<const OpaqueType *>(&type) != nullptr; }
		std::string whyString() const override { return "O"; }
	};

	TypePtr getType(const ASTNode *);
	std::ostream & operator<<(std::ostream &os, Type &type);
}
