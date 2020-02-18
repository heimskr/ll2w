#ifndef PARSER_TYPES_H_
#define PARSER_TYPES_H_

#include <string>
#include <vector>

#include "parser/ASTNode.h"
#include "parser/Enums.h"
#include "parser/StringSet.h"
#include "compiler/WhyInfo.h"

namespace LL2W {
	class StructNode;

	class Type {
		protected:
			enum class TypeType {None, Void, Int, Array, Vector, Float, Pointer, Function, Struct, GlobalTemporary};

		public:
			virtual TypeType typeType() const { return TypeType::None; }
			virtual operator std::string() = 0;
			virtual ~Type() {}
			virtual Type * copy() const = 0;
			virtual int width() const = 0;
			virtual bool operator==(const Type &other) const { return typeType() == other.typeType(); }
			virtual bool operator!=(const Type &other) const { return !(*this == other); }
	};

	struct VoidType: public Type {
		TypeType typeType() const override { return TypeType::Void; }
		VoidType() {}
		virtual operator std::string() override { return "void"; }
		Type * copy() const override { return new VoidType(); }
		int width() const override { return 0; }
	};

	struct IntType: public Type {
		TypeType typeType() const override { return TypeType::Int; }
		int intWidth;
		IntType(int width_): intWidth(width_) {}
		operator std::string() override;
		Type * copy() const override { return new IntType(intWidth); }
		int width() const override { return intWidth; }
		bool operator==(const Type &other) const override;
	};

	struct AggregateType: public Type {
		virtual Type * extractType(const std::vector<int> &indices) const = 0;
	};

	struct ArrayType: public AggregateType {
		TypeType typeType() const override { return TypeType::Array; }
		int count;
		Type *subtype;
		ArrayType(int count_, Type *subtype_): count(count_), subtype(subtype_) {}
		template <typename T>
		ArrayType(int count_, const T &subtype_): count(count_), subtype(new T(subtype_)) {}
		~ArrayType() { delete subtype; }
		operator std::string() override;
		Type * copy() const override { return new ArrayType(count, subtype->copy()); }
		int width() const override { return count * subtype->width(); }
		Type * extractType(const std::vector<int> &) const override { return subtype->copy(); }
		bool operator==(const Type &) const override;
	};

	struct VectorType: public ArrayType {
		TypeType typeType() const override { return TypeType::Vector; }
		using ArrayType::ArrayType;
		operator std::string() override;
		Type * copy() const override { return new VectorType(count, subtype->copy()); }
		bool operator==(const Type &) const override;
	};

	struct FloatType: public Type {
		TypeType typeType() const override { return TypeType::Float; }
		enum class Type: int {Half, Float, Double, FP128, x86_FP80, PPC_FP128};
		FloatType::Type type;
		FloatType(FloatType::Type type_): type(type_) {}
		operator std::string() override;
		LL2W::Type * copy() const override { return new FloatType(type); }
		static Type getType(const std::string &);
		int width() const override;
		bool operator==(const LL2W::Type &) const override;
	};

	struct PointerType: public Type {
		TypeType typeType() const override { return TypeType::Pointer; }
		Type *subtype;
		PointerType(Type *subtype_): subtype(subtype_) {}
		template <typename T>
		PointerType(const T &subtype_): subtype(new T(subtype_)) {}
		~PointerType() { delete subtype; }
		operator std::string() override;
		Type * copy() const override { return new PointerType(subtype->copy()); }
		int width() const override { return WhyInfo::pointerWidth; }
		bool operator==(const Type &) const override;
	};

	class FunctionType: public Type {
		private:
			TypeType typeType() const override { return TypeType::Function; }
			std::string cached = "";

		public:
			Type *returnType;
			std::vector<Type *> argumentTypes;
			bool ellipsis;
			FunctionType(const ASTNode *);
			FunctionType(Type *return_type, std::vector<Type *> &argument_types):
				returnType(return_type), argumentTypes(std::move(argument_types)) {}
			~FunctionType();
			void uncache() { cached.clear(); }
			operator std::string() override;
			Type * copy() const override;
			int width() const override { return WhyInfo::pointerWidth; }
			bool operator==(const Type &) const override;
			bool operator!=(const Type &) const override;
	};

	struct StructType: public AggregateType {
		TypeType typeType() const override { return TypeType::Struct; }
		const std::string *name;
		StructForm form = StructForm::Struct;
		StructShape shape = StructShape::Default;
		const StructNode *node = nullptr;
		StructType(const std::string *name_, StructForm form_ = StructForm::Struct): name(name_), form(form_) {}
		StructType(const StructNode *);
		~StructType();
		operator std::string() override;
		Type * copy() const override { return new StructType(name); }
		int width() const override;
		Type * extractType(const std::vector<int> &indices) const override;
		bool operator==(const Type &) const override;
	};

	/** Global variables are specified without a type indicator. This means that when we encounter a global variable, we
	 *  have to defer its type resolution until everything is done parsing and use a temporary type in the meantime.
	 *  After that, we need to traverse the AST and replace all the temporary types with the known type of the global
	 *  variable. */
	struct GlobalTemporaryType: public Type {
		TypeType typeType() const override { return TypeType::GlobalTemporary; }
		const std::string *globalName;
		GlobalTemporaryType(const std::string *globalName_): globalName(globalName_) {}
		GlobalTemporaryType(const ASTNode *node): GlobalTemporaryType(StringSet::intern(node->extractName())) {}
		operator std::string() override { return "\e[1;4m@" + *globalName + "\e[0m"; }
		Type * copy() const override { return new GlobalTemporaryType(globalName); }
		int width() const override { throw std::runtime_error("Calling GlobalTemporaryType::width() is invalid"); }
	};

	Type * getType(const ASTNode *);
	std::ostream & operator<<(std::ostream &os, Type &type);
}

#endif
