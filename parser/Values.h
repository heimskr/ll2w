#ifndef PARSER_VALUES_H_
#define PARSER_VALUES_H_

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

namespace LL2W {
	class ASTNode;

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
		Value * copy() const override { return new DoubleValue(value); }
		operator std::string() override { return std::to_string(value); }
	};

	struct IntValue: public Value {
		int value;
		IntValue(int value_): value(value_) {}
		IntValue(const std::string &value_): IntValue(atoi(value_.c_str())) {}
		IntValue(const std::string *value_): IntValue(*value_) {}
		Value * copy() const override { return new IntValue(value); }
		operator std::string() override { return std::to_string(value); }
	};

	class VectorValue: public Value {
		private:
			VectorValue(const std::vector<std::pair<Type *, Value *>> &values_): values(values_) {}

		public:
			std::vector<std::pair<Type *, Value *>> values;
			VectorValue(ASTNode *);
			~VectorValue();
			Value * copy() const override;
			operator std::string() override;
	};

	Value * getValue(ASTNode *);
}


#endif
