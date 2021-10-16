#ifndef PARSER_VALUES_H_
#define PARSER_VALUES_H_

#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ASTNode.h"
#include "Enums.h"

namespace LL2W {
	class ASTNode;
	class Type;
	struct Constant;
	class Variable;
	class Function;

	struct Value;
	using ValuePtr = std::shared_ptr<Value>;
	using ConstantPtr = std::shared_ptr<Constant>;

	struct Value {
		virtual operator std::string() = 0;
		virtual ~Value() {}
		virtual ValueType valueType() const = 0;
		virtual ValuePtr copy() const = 0;
		bool isInt() const;
		bool isBool() const;
		bool isNull() const;
		bool isLocal() const;
		bool isGlobal() const;
		bool isGetelementptr() const;
		virtual bool isIntLike() const { return false; }
		virtual long longValue() const { throw std::runtime_error("Value isn't int-like"); }
		int intValue(bool can_warn = true);
		/* Stringifies the Value into something that can be put in a #data section. */
		virtual std::string compile() const = 0;
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
		std::string compile() const override { return std::to_string(value); }
	};

	struct IntValue: public Value {
		long value;
		IntValue(long value_): value(value_) {}
		IntValue(const std::string &);
		IntValue(const std::string *value_): IntValue(*value_) {}
		IntValue(const ASTNode *node): IntValue(node->lexerInfo) {}
		ValueType valueType() const override { return ValueType::Int; }
		ValuePtr copy() const override { return std::make_shared<IntValue>(value); }
		operator std::string() override { return "\e[92m" + std::to_string(value) + "\e[0m"; }
		bool isIntLike() const override { return true; }
		long longValue() const override { return value; }
		std::string compile() const override { return std::to_string(value); }
	};

	struct NullValue: public IntValue {
		NullValue(): IntValue((long) 0) {}
		ValueType valueType() const override { return ValueType::Null; }
		ValuePtr copy() const override { return std::make_shared<NullValue>(); }
		operator std::string() override { return "null"; }
		bool isIntLike() const override { return true; }
		long longValue() const override { return 0; }
		std::string compile() const override { return "0"; }
	};

	struct VectorValue: public Value {
		std::vector<std::pair<TypePtr, ValuePtr>> values;
		VectorValue(const ASTNode *);
		VectorValue(const std::vector<std::pair<TypePtr, ValuePtr>> &values_): values(values_) {}
		ValueType valueType() const override { return ValueType::Vector; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNIMPLEMENTED (Vector)"; }
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
		bool isIntLike() const override { return true; }
		long longValue() const override { return value? 1 : 0; }
		std::string compile() const override { return std::to_string(longValue()); }
	};

	struct VariableValue: public Value {
		protected:
			VariableValue(const std::string *name_): name(name_) {}

		public:
			const std::string *name = nullptr;
			std::string compile() const override { return "UNSUPPORTED (Variable)"; }
	};

	struct LocalValue: public VariableValue {
		std::shared_ptr<Variable> variable = nullptr;
		LocalValue(const std::string *name_): VariableValue(name_) {}
		LocalValue(const std::string &name_): LocalValue(StringSet::intern(name_)) {}
		LocalValue(std::shared_ptr<Variable>);
		LocalValue(const ASTNode *node);
		ValueType valueType() const override { return ValueType::Local; }
		ValuePtr copy() const override { return std::make_shared<LocalValue>(name); }
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Local)"; }
		std::shared_ptr<Variable> getVariable(Function &);
	};

	struct GlobalValue: public VariableValue {
		GlobalValue(const std::string *name_): VariableValue(name_) {}
		GlobalValue(const std::string &name_): GlobalValue(&name_) {}
		GlobalValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::Global; }
		ValuePtr copy() const override { return std::make_shared<GlobalValue>(name); }
		operator std::string() override { return "\e[32m@" + *name + "\e[39m"; }
		std::string compile() const override { return "&" + *name; }
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
		std::string compile() const override { return "UNSUPPORTED (Getelementptr)"; }
	};

	struct VoidValue: public Value {
		ValueType valueType() const override { return ValueType::Void; }
		ValuePtr copy() const override { return std::make_shared<VoidValue>(); }
		operator std::string() override { return "void"; }
		std::string compile() const override { return "0"; }
	};

	struct StructValue: public Value {
		std::vector<ConstantPtr> constants;
		StructValue(const ASTNode *);
		StructValue(const std::vector<ConstantPtr> &constants_): constants(constants_) {}
		ValueType valueType() const override { return ValueType::Struct; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Struct)"; }
	};

	struct ArrayValue: public Value {
		std::vector<ConstantPtr> constants;
		ArrayValue(const ASTNode *);
		ArrayValue(const std::vector<ConstantPtr> &constants_): constants(constants_) {}
		ValueType valueType() const override { return ValueType::Array; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Array)"; }
	};

	struct CStringValue: public Value {
		const std::string *value;
		CStringValue(const std::string *value_): value(value_) {}
		CStringValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::CString; }
		ValuePtr copy() const override { return std::make_shared<CStringValue>(value); }
		operator std::string() override { return "\e[34mc\e[33m\"" + *value + "\"\e[0m"; }
		// Replaces LLVM-style escapes (e.g., "\1B") with WASM-style escapes (e.g., "\x1B").
		std::string reescape() const;
		std::string compile() const override { return "\"" + reescape() + "\""; }
	};

	struct ZeroinitializerValue: public Value {
		ZeroinitializerValue() {}
		ValueType valueType() const override { return ValueType::Zeroinitializer; }
		ValuePtr copy() const override { return std::make_shared<ZeroinitializerValue>(); }
		operator std::string() override { return "zeroinitializer"; }
		std::string compile() const override { return "0"; }
	};

	struct UndefValue: public Value {
		UndefValue() {}
		ValueType valueType() const override { return ValueType::Undef; }
		ValuePtr copy() const override { return std::make_shared<UndefValue>(); }
		operator std::string() override { return "undef"; }
		std::string compile() const override { return "0"; }
	};

	ValuePtr getValue(ASTNode *);
	ValuePtr convertConversion(ASTNode *);
	std::ostream & operator<<(std::ostream &, Value &);
	std::string getName(ValueType);
}

#endif
