#ifndef PARSER_VALUES_H_
#define PARSER_VALUES_H_

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "ASTNode.h"

namespace LL2W {
	class ASTNode;
	struct Type;
	class Constant;

	struct Value {
		virtual operator std::string() = 0;
		virtual ~Value() {}
		virtual Value * copy() const = 0;
	};

	struct DoubleValue: public Value {
		double value;
		DoubleValue(double value_): value(value_) {}
		DoubleValue(const std::string &value_): DoubleValue(std::stod(value_)) {}
		DoubleValue(const std::string *value_): DoubleValue(*value_) {}
		DoubleValue(const ASTNode *node): DoubleValue(node->lexerInfo) {}
		Value * copy() const override { return new DoubleValue(value); }
		operator std::string() override { return std::to_string(value); }
	};

	struct IntValue: public Value {
		int value;
		IntValue(int value_): value(value_) {}
		IntValue(const std::string &value_): IntValue(atoi(value_.c_str())) {}
		IntValue(const std::string *value_): IntValue(*value_) {}
		IntValue(const ASTNode *node): IntValue(node->lexerInfo) {}
		Value * copy() const override { return new IntValue(value); }
		operator std::string() override { return "\e[92m" + std::to_string(value) + "\e[0m"; }
	};

	struct NullValue: public IntValue {
		NullValue(): IntValue(0) {}
		Value * copy() const override { return new NullValue(); }
		operator std::string() override { return "null"; }
	};

	class VectorValue: public Value {
		private:
			VectorValue(const std::vector<std::pair<Type *, Value *>> &values_): values(values_) {}

		public:
			std::vector<std::pair<Type *, Value *>> values;
			VectorValue(const ASTNode *);
			~VectorValue();
			Value * copy() const override;
			operator std::string() override;
	};

	struct BoolValue: public Value {
		bool value;
		BoolValue(bool value_): value(value_) {}
		BoolValue(const std::string &value_): BoolValue(value_ == "true") {}
		BoolValue(const std::string *value_): BoolValue(*value_) {}
		BoolValue(const ASTNode *node): BoolValue(node->lexerInfo) {}
		Value * copy() const override { return new BoolValue(value); }
		operator std::string() override { return value? "true" : "false"; }
	};

	struct VariableValue: public Value {};

	struct LocalValue: public VariableValue {
		const std::string *name;
		LocalValue(const std::string *name_): name(name_) {}
		LocalValue(const std::string &name_): LocalValue(&name_) {}
		LocalValue(const ASTNode *node);
		Value * copy() const override { return new LocalValue(name); }
		operator std::string() override { return "\e[32m%" + *name + "\e[39m"; }
	};

	struct GlobalValue: public VariableValue {
		const std::string *name;
		GlobalValue(const std::string *name_): name(name_) {}
		GlobalValue(const std::string &name_): GlobalValue(&name_) {}
		GlobalValue(const ASTNode *);
		Value * copy() const override { return new GlobalValue(name); }
		operator std::string() override { return "\e[32m@" + *name + "\e[39m"; }
	};

	class GetelementptrValue: public Value {
		private:
			GetelementptrValue(bool inbounds_, Type *type_, Type *ptr_type, Value *variable_,
			                   const std::vector<std::pair<int, long>> &decimals_);

		public:
			bool inbounds = false;
			Type *type, *ptrType;
			Value *variable;
			std::vector<std::pair<int, long>> decimals {};

			GetelementptrValue(ASTNode *inbounds_, ASTNode *type_, ASTNode *ptr_type, ASTNode *variable_,
			                   ASTNode *decimal_list);
			GetelementptrValue(ASTNode *node);
			~GetelementptrValue();
			Value * copy() const override {
				return new GetelementptrValue(inbounds, type->copy(), ptrType->copy(), variable->copy(), decimals);
			}
			operator std::string() override;
	};

	struct VoidValue: public Value {
		Value * copy() const override { return new VoidValue(); }
		operator std::string() override { return "void"; }
	};

	class StructValue: public Value {
		private:
			StructValue(std::vector<Constant *> &&constants_): constants(constants_) {}

		public:
			std::vector<Constant *> constants;
			StructValue(const ASTNode *);
			~StructValue();
			Value * copy() const override;
			operator std::string() override;
	};

	class ArrayValue: public Value {
		private:
			ArrayValue(const std::vector<Constant *> &constants_): constants(constants_) {}

		public:
			std::vector<Constant *> constants;
			ArrayValue(const ASTNode *);
			~ArrayValue();
			Value * copy() const override;
			operator std::string() override;
	};

	struct CStringValue: public Value {
		const std::string *value;
		CStringValue(const std::string *value_): value(value_) {}
		CStringValue(const ASTNode *);
		Value * copy() const override { return new CStringValue(value); }
		operator std::string() override { return "\e[34mc\e[33m\"" + *value + "\"\e[0m"; }
	};

	struct ZeroinitializerValue: public Value {
		ZeroinitializerValue() {}
		Value * copy() const override { return new ZeroinitializerValue(); }
		operator std::string() override { return "zeroinitializer"; }
	};

	// TODO: ArrayValue

	Value * getValue(ASTNode *);
	std::ostream & operator<<(std::ostream &, Value &);
}

#endif
