#pragma once

#include <cstdlib>
#include <format>
#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "ASTNode.h"
#include "Enums.h"
#include "util/Makeable.h"

namespace llvm {
	class ConstantArray;
	class ConstantDataArray;
	class ConstantStruct;
	class Value;
}

namespace LL2W {
	class ASTNode;
	class Type;
	class Constant;
	class Variable;
	class Function;
	struct IcmpNode;
	struct LogicNode;

	class Value;
	using ValuePtr = std::shared_ptr<Value>;
	using ConstantPtr = std::shared_ptr<Constant>;

	class Value {
		public:
			virtual operator std::string() = 0;
			virtual ~Value() = default;
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
			int intValue(bool can_warn = true, bool allow_wrap = false);
			bool overflows() const;
			/* Stringifies the Value into something that can be put in a #data section. */
			virtual std::string compile() const = 0;
	};

	struct DoubleValue: Value {
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

	struct IntValue: Value, Makeable<IntValue> {
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

	struct NullValue: IntValue {
		NullValue(): IntValue((long) 0) {}
		ValueType valueType() const override { return ValueType::Null; }
		ValuePtr copy() const override { return std::make_shared<NullValue>(); }
		operator std::string() override { return "null"; }
		bool isIntLike() const override { return true; }
		long longValue() const override { return 0; }
		std::string compile() const override { return "0"; }
	};

	struct VectorValue: Value {
		std::vector<std::pair<TypePtr, ValuePtr>> values;
		VectorValue(const ASTNode *);
		VectorValue(const std::vector<std::pair<TypePtr, ValuePtr>> &values_): values(values_) {}
		ValueType valueType() const override { return ValueType::Vector; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNIMPLEMENTED (Vector)"; }
	};

	struct BoolValue: Value {
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

	struct VariableValue: Value {
		protected:
			VariableValue(const std::string *name): name(name) {}

		public:
			const std::string *name = nullptr;
			std::string compile() const override { return "UNSUPPORTED (Variable)"; }
	};

	struct LocalValue: VariableValue, Makeable<LocalValue> {
		std::shared_ptr<Variable> variable = nullptr;
		LocalValue(const std::string *name);
		LocalValue(const std::string &name): LocalValue(StringSet::intern(name)) {}
		LocalValue(std::shared_ptr<Variable>);
		LocalValue(const ASTNode *node);
		ValueType valueType() const override { return ValueType::Local; }
		ValuePtr copy() const override { return std::make_shared<LocalValue>(name); }
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Local)"; }
		std::shared_ptr<Variable> getVariable(Function &);
	};

	struct GlobalValue: VariableValue, Makeable<GlobalValue> {
		GlobalValue(const std::string *name);
		GlobalValue(const std::string &name): GlobalValue(StringSet::intern(name)) {}
		GlobalValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::Global; }
		ValuePtr copy() const override { return std::make_shared<GlobalValue>(name); }
		operator std::string() override { return "\e[32m" + *name + "\e[39m"; }
		std::string compile() const override { return "&" + name->substr(1); }
	};

	struct GetelementptrValue: Value {
		bool inbounds = false;
		TypePtr type, ptrType;
		ValuePtr variable;
		// The first element represents the width of the integer type.
		std::vector<std::pair<long, std::variant<long, const std::string *>>> decimals {};

		GetelementptrValue(ASTNode *inbounds_, ASTNode *type_, ASTNode *ptr_type, ASTNode *variable_, ASTNode *decimal_list);
		GetelementptrValue(bool inbounds_, TypePtr type_, TypePtr ptr_type, ValuePtr variable_, decltype(decimals) decimals);
		GetelementptrValue(const ASTNode *);

		ValueType valueType() const override { return ValueType::Getelementptr; }
		ValuePtr copy() const override { return std::make_shared<GetelementptrValue>(inbounds, type->copy(), ptrType->copy(), variable->copy(), decimals); }
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Getelementptr)"; }
	};

	struct IcmpValue: Value, Makeable<IcmpValue> {
		IcmpCond cond;
		ConstantPtr left, right;
		IcmpValue(ASTNode *cond_, ASTNode *left_, ASTNode *right_);
		IcmpValue(IcmpCond cond_, ConstantPtr left_, ConstantPtr right_): cond(cond_), left(left_), right(right_) {}
		IcmpValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::Icmp; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Icmp)"; }
		std::shared_ptr<IcmpNode> makeNode(std::shared_ptr<Variable>) const;
	};

	struct LogicValue: Value, Makeable<LogicValue> {
		LogicType type;
		ConstantPtr left, right;
		LogicValue(ASTNode *type_, ASTNode *left_, ASTNode *right_);
		LogicValue(LogicType type_, ConstantPtr left_, ConstantPtr right_): type(type_), left(left_), right(right_) {}
		LogicValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::Logic; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Logic)"; }
		std::shared_ptr<LogicNode> makeNode(std::shared_ptr<Variable>) const;
	};

	struct VoidValue: Value, Makeable<VoidValue> {
		VoidValue() = default;
		ValueType valueType() const override { return ValueType::Void; }
		ValuePtr copy() const override { return std::make_shared<VoidValue>(); }
		operator std::string() override { return "void"; }
		std::string compile() const override { return "0"; }
	};

	struct StructValue: Value, Makeable<StructValue> {
		std::vector<ConstantPtr> constants;
		bool packed = false;
		StructValue(const ASTNode *);
		StructValue(std::vector<ConstantPtr> constants, bool packed = false):
			constants(std::move(constants)), packed(packed) {}
		StructValue(const llvm::ConstantStruct &);
		ValueType valueType() const override { return ValueType::Struct; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Struct)"; }
	};

	struct ArrayValue: Value, Makeable<ArrayValue> {
		std::vector<ConstantPtr> constants;
		ArrayValue(const ASTNode *);
		ArrayValue(std::vector<ConstantPtr> constants):
			constants(std::move(constants)) {}
		ArrayValue(const llvm::ConstantArray &);
		ArrayValue(const llvm::ConstantDataArray &);
		ValueType valueType() const override { return ValueType::Array; }
		ValuePtr copy() const override;
		operator std::string() override;
		std::string compile() const override { return "UNSUPPORTED (Array)"; }
	};

	struct CStringValue: Value, Makeable<CStringValue> {
		std::string value;
		CStringValue(std::string_view value):
			value(value) {}
		CStringValue(const ASTNode *);
		ValueType valueType() const override { return ValueType::CString; }
		ValuePtr copy() const override { return std::make_shared<CStringValue>(value); }
		operator std::string() override { return "\e[34mc\e[33m\"" + std::string(value) + "\"\e[0m"; }
		// Replaces LLVM-style escapes (e.g., "\1B") with WASM-style escapes (e.g., "\x1B").
		std::string reescape() const;
		std::string compile() const override { return "\"" + reescape() + "\""; }
	};

	struct ZeroinitializerValue: Value, Makeable<ZeroinitializerValue> {
		ZeroinitializerValue() = default;
		ValueType valueType() const override { return ValueType::Zeroinitializer; }
		ValuePtr copy() const override { return std::make_shared<ZeroinitializerValue>(); }
		operator std::string() override { return "zeroinitializer"; }
		std::string compile() const override { return "0"; }
	};

	struct UndefValue: Value, Makeable<UndefValue> {
		UndefValue() = default;
		ValueType valueType() const override { return ValueType::Undef; }
		ValuePtr copy() const override { return std::make_shared<UndefValue>(); }
		operator std::string() override { return "undef"; }
		bool isIntLike() const override { return true; }
		long longValue() const override { return 0; }
		std::string compile() const override { return "0"; }
	};

	struct PoisonValue: Value, Makeable<PoisonValue> {
		PoisonValue() = default;
		ValueType valueType() const override { return ValueType::Poison; }
		ValuePtr copy() const override { return std::make_shared<PoisonValue>(); }
		operator std::string() override { return "poison"; }
		bool isIntLike() const override { return true; }
		long longValue() const override { return 0; }
		std::string compile() const override { return "0"; }
	};

	ValuePtr getValue(ASTNode *);
	ValuePtr convertConversion(ASTNode *);
	std::ostream & operator<<(std::ostream &, Value &);
	std::string getName(ValueType);
}
