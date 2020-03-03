#ifndef PARSER_VALUES_H_
#define PARSER_VALUES_H_

#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ASTNode.h"

namespace LL2W {
	class ASTNode;
	class Type;
	class Constant;
	class Variable;

	enum class ValueType {
		Double, Int, Null, Vector, Bool, Local, Global, Getelementptr, Void, Struct, Array, CString, Zeroinitializer,
		Undef
	};

	struct Value {
		virtual operator std::string() = 0;
		virtual ~Value() {}
		virtual ValueType valueType() const = 0;
		virtual Value * copy() const = 0;
	};

	struct DoubleValue: public Value {
		const double value;
		const std::string *original;
		DoubleValue(double value_): value(value_), original(StringSet::intern(std::to_string(value_))) {}
		DoubleValue(const std::string &value_): value(std::stod(value_)), original(StringSet::intern(value_)) {}
		DoubleValue(const std::string *value_): value(std::stod(*value_)), original(value_) {}
		DoubleValue(const ASTNode *node): DoubleValue(node->lexerInfo) {}
		ValueType valueType() const override { return ValueType::Double; }
		Value * copy() const override { return new DoubleValue(value); }
		operator std::string() override { return *original; }
	};

	struct IntValue: public Value {
		int value;
		IntValue(int value_): value(value_) {}
		IntValue(const std::string &value_): IntValue(atoi(value_.c_str())) {}
		IntValue(const std::string *value_): IntValue(*value_) {}
		IntValue(const ASTNode *node): IntValue(node->lexerInfo) {}
		ValueType valueType() const override { return ValueType::Int; }
		Value * copy() const override { return new IntValue(value); }
		operator std::string() override { return "\e[92m" + std::to_string(value) + "\e[0m"; }
	};

	struct NullValue: public IntValue {
		NullValue(): IntValue(0) {}
		ValueType valueType() const override { return ValueType::Null; }
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
			ValueType valueType() const override { return ValueType::Vector; }
			Value * copy() const override;
			operator std::string() override;
	};

	struct BoolValue: public Value {
		bool value;
		BoolValue(bool value_): value(value_) {}
		BoolValue(const std::string &value_): BoolValue(value_ == "true") {}
		BoolValue(const std::string *value_): BoolValue(*value_) {}
		BoolValue(const ASTNode *node): BoolValue(node->lexerInfo) {}
		ValueType valueType() const override { return ValueType::Bool; }
		Value * copy() const override { return new BoolValue(value); }
		operator std::string() override { return value? "true" : "false"; }
	};

	struct VariableValue: public Value {};

	struct LocalValue: public VariableValue {
		const std::string *name;
		std::shared_ptr<Variable> variable = nullptr;
		LocalValue(const std::string *name_): name(name_) {}
		LocalValue(const std::string &name_): LocalValue(&name_) {}
		LocalValue(const ASTNode *node);
		ValueType valueType() const override { return ValueType::Local; }
		Value * copy() const override { return new LocalValue(name); }
		operator std::string() override;
	};

	struct GlobalValue: public VariableValue {
		const std::string *name;
		GlobalValue(const std::string *name_): name(name_) {}
		GlobalValue(const std::string &name_): GlobalValue(&name_) {}
		GlobalValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::Global; }
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
			std::vector<std::pair<int, long>> decimals {}; // the ints represent the width of the integer type

			GetelementptrValue(ASTNode *inbounds_, ASTNode *type_, ASTNode *ptr_type, ASTNode *variable_,
			                   ASTNode *decimal_list);
			GetelementptrValue(ASTNode *node);
			~GetelementptrValue();
			ValueType valueType() const override { return ValueType::Getelementptr; }
			Value * copy() const override {
				return new GetelementptrValue(inbounds, type->copy(), ptrType->copy(), variable->copy(), decimals);
			}
			operator std::string() override;
	};

	struct VoidValue: public Value {
		ValueType valueType() const override { return ValueType::Void; }
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
			ValueType valueType() const override { return ValueType::Struct; }
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
			ValueType valueType() const override { return ValueType::Array; }
			Value * copy() const override;
			operator std::string() override;
	};

	struct CStringValue: public Value {
		const std::string *value;
		CStringValue(const std::string *value_): value(value_) {}
		CStringValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::CString; }
		Value * copy() const override { return new CStringValue(value); }
		operator std::string() override { return "\e[34mc\e[33m\"" + *value + "\"\e[0m"; }
	};

	struct ZeroinitializerValue: public Value {
		ZeroinitializerValue() {}
		ValueType valueType() const override { return ValueType::Zeroinitializer; }
		Value * copy() const override { return new ZeroinitializerValue(); }
		operator std::string() override { return "zeroinitializer"; }
	};

	struct UndefValue: public Value {
		UndefValue() {}
		ValueType valueType() const override { return ValueType::Undef; }
		Value * copy() const override { return new UndefValue(); }
		operator std::string() override { return "undef"; }
	};

	Value * getValue(ASTNode *);
	std::ostream & operator<<(std::ostream &, Value &);
}

#endif
