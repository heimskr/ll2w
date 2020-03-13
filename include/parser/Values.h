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
	struct Constant;
	class Variable;

	enum class ValueType {
		Double, Int, Null, Vector, Bool, Local, Global, Getelementptr, Void, Struct, Array, CString, Zeroinitializer,
		Undef
	};

	struct Value;
	using ValuePtr = std::shared_ptr<Value>;
	using ConstantPtr = std::shared_ptr<Constant>;

	struct Value {
		virtual operator std::string() = 0;
		virtual ~Value() {}
		virtual ValueType valueType() const = 0;
		virtual ValuePtr copy() const = 0;
	};

	struct DoubleValue: public Value {
		const double value;
		const std::string *original;
		DoubleValue(double value_): value(value_), original(StringSet::intern(std::to_string(value_))) {}
		DoubleValue(const std::string &value_): value(std::stod(value_)), original(StringSet::intern(value_)) {}
		DoubleValue(const std::string *value_): value(std::stod(*value_)), original(value_) {}
		DoubleValue(const ASTNode *node): DoubleValue(node->lexerInfo) {}
		ValueType valueType() const override { return ValueType::Double; }
		ValuePtr copy() const override { return std::make_shared<DoubleValue>(value); }
		operator std::string() override { return *original; }
	};

	struct IntValue: public Value {
		int value;
		IntValue(int value_): value(value_) {}
		IntValue(const std::string &value_): IntValue(atoi(value_.c_str())) {}
		IntValue(const std::string *value_): IntValue(*value_) {}
		IntValue(const ASTNode *node): IntValue(node->lexerInfo) {}
		ValueType valueType() const override { return ValueType::Int; }
		ValuePtr copy() const override { return std::make_shared<IntValue>(value); }
		operator std::string() override { return "\e[92m" + std::to_string(value) + "\e[0m"; }
	};

	struct NullValue: public IntValue {
		NullValue(): IntValue(0) {}
		ValueType valueType() const override { return ValueType::Null; }
		ValuePtr copy() const override { return std::make_shared<NullValue>(); }
		operator std::string() override { return "null"; }
	};

	struct VectorValue: public Value {
		std::vector<std::pair<TypePtr, ValuePtr>> values;
		VectorValue(const ASTNode *);
		VectorValue(const std::vector<std::pair<TypePtr, ValuePtr>> &values_): values(values_) {}
		ValueType valueType() const override { return ValueType::Vector; }
		ValuePtr copy() const override;
		operator std::string() override;
	};

	struct BoolValue: public Value {
		bool value;
		BoolValue(bool value_): value(value_) {}
		BoolValue(const std::string &value_): BoolValue(value_ == "true") {}
		BoolValue(const std::string *value_): BoolValue(*value_) {}
		BoolValue(const ASTNode *node): BoolValue(node->lexerInfo) {}
		ValueType valueType() const override { return ValueType::Bool; }
		ValuePtr copy() const override { return std::make_shared<BoolValue>(value); }
		operator std::string() override { return value? "true" : "false"; }
	};

	struct VariableValue: public Value {
		protected:
			VariableValue(const std::string *name_): name(name_) {}

		public:
			const std::string *name = nullptr;
	};

	struct LocalValue: public VariableValue {
		std::shared_ptr<Variable> variable = nullptr;
		LocalValue(const std::string *name_): VariableValue(name_) {}
		LocalValue(const std::string &name_): LocalValue(&name_) {}
		LocalValue(const ASTNode *node);
		ValueType valueType() const override { return ValueType::Local; }
		ValuePtr copy() const override { return std::make_shared<LocalValue>(name); }
		operator std::string() override;
	};

	struct GlobalValue: public VariableValue {
		GlobalValue(const std::string *name_): VariableValue(name_) {}
		GlobalValue(const std::string &name_): GlobalValue(&name_) {}
		GlobalValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::Global; }
		ValuePtr copy() const override { return std::make_shared<GlobalValue>(name); }
		operator std::string() override { return "\e[32m@" + *name + "\e[39m"; }
	};

	struct GetelementptrValue: public Value {
		bool inbounds = false;
		TypePtr type, ptrType;
		ValuePtr variable;
		std::vector<std::pair<int, long>> decimals {}; // the ints represent the width of the integer type

		GetelementptrValue(ASTNode *inbounds_, ASTNode *type_, ASTNode *ptr_type, ASTNode *variable_,
							ASTNode *decimal_list);
		GetelementptrValue(bool inbounds_, TypePtr type_, TypePtr ptr_type, ValuePtr variable_,
							const std::vector<std::pair<int, long>> &decimals_);
		GetelementptrValue(ASTNode *node);
		ValueType valueType() const override { return ValueType::Getelementptr; }
		ValuePtr copy() const override {
			return std::make_shared<GetelementptrValue>(inbounds, type->copy(), ptrType->copy(), variable->copy(),
				decimals);
		}
		operator std::string() override;
	};

	struct VoidValue: public Value {
		ValueType valueType() const override { return ValueType::Void; }
		ValuePtr copy() const override { return std::make_shared<VoidValue>(); }
		operator std::string() override { return "void"; }
	};

	struct StructValue: public Value {
		std::vector<ConstantPtr> constants;
		StructValue(const ASTNode *);
		StructValue(const std::vector<ConstantPtr> &constants_): constants(constants_) {}
		ValueType valueType() const override { return ValueType::Struct; }
		ValuePtr copy() const override;
		operator std::string() override;
	};

	struct ArrayValue: public Value {
		std::vector<ConstantPtr> constants;
		ArrayValue(const ASTNode *);
		ArrayValue(const std::vector<ConstantPtr> &constants_): constants(constants_) {}
		ValueType valueType() const override { return ValueType::Array; }
		ValuePtr copy() const override;
		operator std::string() override;
	};

	struct CStringValue: public Value {
		const std::string *value;
		CStringValue(const std::string *value_): value(value_) {}
		CStringValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::CString; }
		ValuePtr copy() const override { return std::make_shared<CStringValue>(value); }
		operator std::string() override { return "\e[34mc\e[33m\"" + *value + "\"\e[0m"; }
	};

	struct ZeroinitializerValue: public Value {
		ZeroinitializerValue() {}
		ValueType valueType() const override { return ValueType::Zeroinitializer; }
		ValuePtr copy() const override { return std::make_shared<ZeroinitializerValue>(); }
		operator std::string() override { return "zeroinitializer"; }
	};

	struct UndefValue: public Value {
		UndefValue() {}
		ValueType valueType() const override { return ValueType::Undef; }
		ValuePtr copy() const override { return std::make_shared<UndefValue>(); }
		operator std::string() override { return "undef"; }
	};

	ValuePtr getValue(ASTNode *);
	std::ostream & operator<<(std::ostream &, Value &);
}

#endif
