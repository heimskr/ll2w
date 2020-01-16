#ifndef PARSER_TYPES_H_
#define PARSER_TYPES_H_

#include <string>

namespace LL2W {
	struct ASTNode;

	struct Type {
		virtual operator std::string() = 0;
		virtual ~Type() {}
	};

	struct IntType: public Type {
		int width;
		IntType(int width_): width(width_) {}
		operator std::string() override;
	};

	template <typename T>
	struct ArrayType: public Type {
		int count;
		T subtype;
		ArrayType(int count_, const T &subtype_): count(count_), subtype(subtype_) {}
		operator std::string() override {
			return "[" + std::to_string(count) + " x " + std::string(subtype) + "]";
		}
	};

	template <typename T>
	struct VectorType: public ArrayType<T> {
		using ArrayType<T>::ArrayType;
		operator std::string() override {
			return "<" + std::to_string(this->count) + " x " + std::string(this->subtype) + ">";
		}
	};

	struct FloatType: public Type {
		enum class Type: int {Half, Double, FP128, x86_FP80, PPC_FP128};
		FloatType::Type type;
		FloatType(FloatType::Type type_): type(type_) {}
		operator std::string() override;
	};

	template <typename T>
	struct PointerType: public Type {
		T subtype;
		PointerType(const T &subtype_): subtype(subtype_) {}
		operator std::string() override { return std::string(subtype) + " *"; }
	};

	class FunctionType: public Type {
		private:
			std::string cached;

		public:
			const ASTNode *node;
			FunctionType(ASTNode *node_): node(node_) {}
			operator std::string() override;
	};

	Type * getType(ASTNode *);
}

#endif
