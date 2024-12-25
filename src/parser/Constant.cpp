#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/Constant.h"
#include "parser/Lexer.h"
#include "util/Timer.h"
#include "util/Util.h"

#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalAlias.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_os_ostream.h>

#include <iostream>
#include <print>
#include <sstream>

namespace LL2W {
	Constant::Constant() = default;

	Constant::Constant(TypePtr type, ValuePtr value):
		type(std::move(type)),
		value(std::move(value)) {}

	Constant::Constant(TypePtr type, ValuePtr value, const ParAttrs &parattrs_, Conversion conversion_, ConstantPtr conversion_source, TypePtr conversion_type):
		type(std::move(type)),
		value(std::move(value)),
		parattrs(parattrs_),
		conversion(conversion_),
		conversionSource(conversion_source),
		conversionType(conversion_type) {}

	Constant::Constant(const ASTNode *node, TypePtr type_hint) {
		if (node->symbol == LLVMTOK_DECIMAL) {
			if (!type_hint) {
				throw std::runtime_error("Constant::Constant: type hint expected for decimal node");
			}
			type = type_hint;
			value = std::make_shared<IntValue>(node);
		} else if (node->symbol == LLVMTOK_NULL) {
			if (!type_hint) {
				throw std::runtime_error("Constant::Constant: type hint expected for null node");
			}
			type = type_hint;
			value = std::make_shared<NullValue>();
		} else if (node->symbol == LLVMTOK_PVAR) {
			if (!type_hint) {
				throw std::runtime_error("Constant::Constant: type hint expected for pvar node");
			}
			type = type_hint;
			value = std::make_shared<LocalValue>(node);
		} else if (node->symbol == LLVMTOK_GVAR) {
			if (!type_hint) {
				throw std::runtime_error("Constant::Constant: type hint expected for gvar node");
			}
			type = type_hint;
			value = std::make_shared<GlobalValue>(node);
		} else if (node->symbol == LLVM_CONVERSION_EXPR) {
			// if (!type_hint)
			// 	throw std::runtime_error("Constant::Constant: type hint expected for conversion expression node");
			type = type_hint;
			value = nullptr;
			for (const std::pair<const Conversion, std::string> &pair: conversion_map) {
				if (*node->lexerInfo == pair.second) {
					conversion = pair.first;
					break;
				}
			}
			conversionSource = std::make_shared<Constant>(node->at(0));
			conversionType = getType(node->at(1));
		} else if (node->symbol == LLVMTOK_GETELEMENTPTR) {
			if (!type_hint) {
				throw std::runtime_error("Constant::Constant: type hint expected for getelementptr node");
			}
			type = type_hint;
			value = std::make_shared<GetelementptrValue>(node);
		} else if (node->symbol == LLVMTOK_BOOL) {
			type = IntType::make(8, false);
			value = std::make_shared<BoolValue>(node->lexerInfo);
		} else if (node->symbol != LLVM_CONSTANT) {
			node->debug();
			throw std::runtime_error("Constant::Constant: node lacks a supported symbol");
		} else if (node->size() == 1) {
			// Just a gvar here.
			type = getType(node->at(0));
			value = getValue(node->at(0));
		} else {
			type = getType(node->at(0));

			ASTNode *value_node = node->at(1);
			if (GetelementptrValue *gep_value = dynamic_cast<GetelementptrValue *>(value_node)) {
				value = gep_value->copy();
			} else if (value_node->symbol == LLVM_CONVERSION_EXPR) {
				for (const std::pair<const Conversion, std::string> &pair: conversion_map) {
					if (*value_node->lexerInfo == pair.second) {
						conversion = pair.first;
						break;
					}
				}
				value = nullptr;
				conversionSource = std::make_shared<Constant>(value_node->at(0));
				conversionType = getType(value_node->at(1));
			} else {
				value = getValue(value_node);
			}

			if (2 < node->size()) {
				parattrs = {*node->at(2)};
			}
		}
	}

	ConstantPtr Constant::copy() const {
		return std::make_shared<Constant>(type? type->copy() : nullptr, value? value->copy() : nullptr, parattrs, conversion,
			conversionSource? conversionSource->copy() : nullptr,
			conversionType? conversionType->copy() : nullptr);
	}

	ConstantPtr Constant::convert() const {
		if (value) {
			return copy();
		}

		if (!conversionSource) {
			std::cerr << *this << "\n";
			throw std::runtime_error("Constant has neither a value nor a conversion source in Constant::convert()");
		}

		if (conversion != Conversion::Ptrtoint && conversion != Conversion::Inttoptr &&
		    conversion != Conversion::Bitcast) {
			std::cerr << *this << "\n";
			throw std::runtime_error("Unsupported conversion in Constant::convert(): " + conversion_map.at(conversion));
		}

		if (!conversionSource->value) {
			// TODO: recursive conversion?
			std::cerr << *this << "\n";
			throw std::runtime_error("Conversion source has no value in Constant::convert()");
		}

		return Constant::make(conversionType->copy(), conversionSource->value->copy(), parattrs, Conversion::None, nullptr, nullptr);
	}

	Constant::operator std::string() const {
		std::stringstream out;

		if (type) {
			out << std::string(*type);
		} else {
			out << "\e[31mnulltype\e[39m";
		}

		if (std::string parattrs_str = parattrs; !parattrs_str.empty()) {
			out << ' ' << parattrs_str;
		}

		if (value) {
			out << ' ' << std::string(*value);
		} else if (conversion != Conversion::None) {
			out << " \e[91m" << conversion_map.at(conversion) << "\e[39m \e[2m(\e[22m" << std::string(*conversionSource) << " to " << std::string(*conversionType) << "\e[2m)\e[22m";
		}

		return out.str();
	}

	ConstantPtr Constant::fromLLVM(const llvm::Value &llvm_value) {
		Timer timer{"Constant::fromLLVM"};

		if (auto *global_alias = llvm::dyn_cast<llvm::GlobalAlias>(&llvm_value)) {
			return Constant::fromLLVM(*global_alias->getAliasee());
		}

		ConstantPtr out = std::shared_ptr<Constant>(new Constant);

		if (auto *int_constant = llvm::dyn_cast<llvm::ConstantInt>(&llvm_value)) {
			out->type = IntType::make(int_constant->getBitWidth());
			out->value = IntValue::make(int_constant->getZExtValue());
			return out;
		}

		if (auto *struct_constant = llvm::dyn_cast<llvm::ConstantStruct>(&llvm_value)) {
			out->type = StructType::make(*struct_constant->getType());
			out->value = StructValue::make(*struct_constant);
			return out;
		}

		if (auto *array_constant = llvm::dyn_cast<llvm::ConstantArray>(&llvm_value)) {
			out->type = ArrayType::make(array_constant->getNumOperands(), Type::fromLLVM(*array_constant->getType()));
			out->value = ArrayValue::make(*array_constant);
			return out;
		}

		if (auto *data_constant = llvm::dyn_cast<llvm::ConstantDataArray>(&llvm_value)) {
			out->type = Type::fromLLVM(*data_constant->getType());

			if (data_constant->isCString()) {
				out->value = CStringValue::make(data_constant->getAsCString());
			} else {
				out->value = ArrayValue::make(*data_constant);
			}

			return out;
		}

		if (auto *expr_constant = llvm::dyn_cast<llvm::ConstantExpr>(&llvm_value)) {
			std::string_view op = expr_constant->getOpcodeName();

			if (op == "getelementptr") {
				Timer timer{"Constant::getelementptr"};
				out->type = Type::fromLLVM(*llvm_value.getType());
				const llvm::Constant *base = expr_constant->getOperand(0);
				std::vector<std::pair<long, std::variant<long, const std::string *>>> decimals;
				for (unsigned i = 1; i < expr_constant->getNumOperands(); ++i) {
					llvm::ConstantInt &decimal = llvm::cast<llvm::ConstantInt>(*expr_constant->getOperand(i));
					decimals.emplace_back(decimal.getBitWidth(), static_cast<long>(decimal.getZExtValue()));
				}
				auto source_type = Type::fromLLVM(*llvm::cast<llvm::GetElementPtrInst>(expr_constant->getAsInstruction())->getSourceElementType()); // TODO: memleak?
				auto pointer_type = PointerType::make(source_type);
				out->value = std::make_shared<GetelementptrValue>(true /* TODO */, std::move(source_type), std::move(pointer_type), Constant::fromLLVM(*base)->value, std::move(decimals));
				return out;
			}

			if (op == "inttoptr" || op == "ptrtoint") {
				out->type = Type::fromLLVM(*llvm_value.getType());
				out->value = Constant::fromLLVM(*expr_constant->getOperand(0))->value;
				return out;
			}

			dump(*expr_constant);
			throw std::runtime_error(std::format("Unknown ConstantExpr opcode: {}", op));
		}

		if (auto *global_constant = llvm::dyn_cast<llvm::GlobalVariable>(&llvm_value)) {
			if (global_constant->getNumOperands() > 0) {
				assert(global_constant->getNumOperands() == 1);
				out->type = PointerType::make(Type::fromLLVM(*global_constant->getOperand(0)->getType()));
			} else {
				out->type = OpaqueType::make();
			}
			out->value = GlobalValue::make('@' + global_constant->getName().str());
			return out;
		}

		if (auto *null_constant = llvm::dyn_cast<llvm::ConstantPointerNull>(&llvm_value)) {
			out->type = PointerType::makeOpaque();
			out->value = std::make_shared<NullValue>();
			return out;
		}

		if (auto *function_value = llvm::dyn_cast<llvm::Function>(&llvm_value)) {
			out->type = Type::fromLLVM(*function_value->getType());
			out->value = GlobalValue::make('@' + function_value->getName().str());
			return out;
		}

		if (auto *zero_value = llvm::dyn_cast<llvm::ConstantAggregateZero>(&llvm_value)) {
			out->type = Type::fromLLVM(*zero_value->getType());
			out->value = ZeroinitializerValue::make();
			return out;
		}

		if (llvm::isa<llvm::UndefValue>(llvm_value)) {
			out->type = nullptr;
			out->value = UndefValue::make();
			return out;
		}

		if (llvm::isa<llvm::MetadataAsValue>(llvm_value)) {
			return out;
		}

		if (auto *inst = llvm::dyn_cast<llvm::AllocaInst>(&llvm_value)) {
			out->type = PointerType::make(Type::fromLLVM(*inst->getAllocatedType()));
			out->value = LocalValue::make(getOperandName(*inst));
			return out;
		}

		if (auto *inst = llvm::dyn_cast<llvm::Instruction>(&llvm_value)) {
			out->type = Type::fromLLVM(*inst->getType());
			out->value = LocalValue::make(getOperandName(*inst));
			return out;
		}

		if (auto *argument = llvm::dyn_cast<llvm::Argument>(&llvm_value)) {
			out->type = Type::fromLLVM(*argument->getType());
			out->value = LocalValue::make(getOperandName(*argument));
			return out;
		}

		llvm::raw_os_ostream os(error() << "Constant: ");
		llvm_value.print(os, true);
		(os << "\n").flush();

		std::println(error(), "ValueID: {}", static_cast<int>(llvm_value.getValueID()));
		throw std::invalid_argument("Invalid LLVM constant");
	}

	TypePtr Constant::refineType(const Program &program) const {
		if (type->isOpaque()) {
			if (value->isGlobal()) {
				const auto *name = dynamic_cast<const GlobalValue &>(*value).name;
				GlobalVarDef *def = program.globals.at(*name);
				return PointerType::make(def->type);
			}
		}

		return type;
	}

	std::ostream & operator<<(std::ostream &os, const Constant &constant) {
		return os << std::string(constant);
	}
}