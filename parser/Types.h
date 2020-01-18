#ifndef PARSER_TYPES_H_
#define PARSER_TYPES_H_

#include <string>
#include <vector>

namespace LL2W {
	class ASTNode;

	struct Type {
		virtual operator std::string() = 0;
		virtual ~Type() {}
		virtual Type * copy() const = 0;
	};

	struct VoidType: public Type {
		VoidType() {}
		virtual operator std::string() override { return "void"; }
		Type * copy() const override { return new VoidType(); }
	};

	struct IntType: public Type {
		int width;
		IntType(int width_): width(width_) {}
		operator std::string() override;
		Type * copy() const override { return new IntType(width); }
	};

	struct ArrayType: public Type {
		int count;
		Type *subtype;
		ArrayType(int count_, Type *subtype_): count(count_), subtype(subtype_) {}
		template <typename T>
		ArrayType(int count_, const T &subtype_): count(count_), subtype(new T(subtype_)) {}
		~ArrayType() { delete subtype; }
		operator std::string() override {
			return "[" + std::to_string(count) + " x " + std::string(*subtype) + "]";
		}
		Type * copy() const override { return new ArrayType(count, subtype->copy()); }
	};

	struct VectorType: public ArrayType {
		using ArrayType::ArrayType;
		operator std::string() override {
			return "<" + std::to_string(this->count) + " x " + std::string(*this->subtype) + ">";
		}
		Type * copy() const override { return new VectorType(count, subtype->copy()); }
	};

	struct FloatType: public Type {
		enum class Type: int {Half, Double, FP128, x86_FP80, PPC_FP128};
		FloatType::Type type;
		FloatType(FloatType::Type type_): type(type_) {}
		operator std::string() override;
		LL2W::Type * copy() const override { return new FloatType(type); }
		static Type getType(const std::string &);
	};

	struct PointerType: public Type {
		Type *subtype;
		PointerType(Type *subtype_): subtype(subtype_) {}
		template <typename T>
		PointerType(const T &subtype_): subtype(new T(subtype_)) {}
		~PointerType() { delete subtype; }
		operator std::string() override { return std::string(*subtype) + " *"; }
		Type * copy() const override { return new PointerType(subtype->copy()); }
	};

	class FunctionType: public Type {
		private:
			std::string cached = "";

		public:
			Type *returnType;
			std::vector<Type *> argumentTypes;
			bool ellipse;
			FunctionType(const ASTNode *);
			FunctionType(Type *return_type, std::vector<Type *> &argument_types):
				returnType(return_type), argumentTypes(std::move(argument_types)) {}
			~FunctionType();
			void uncache() { cached.clear(); }
			operator std::string() override;
			Type * copy() const override;
	};

	struct StructType: public Type {
		const std::string *name;
		StructType(const std::string *name_): name(name_) {}
		operator std::string() override { return *name; }
		Type * copy() const override { return new StructType(name); }
	};

	Type * getType(const ASTNode *);
}

#endif
