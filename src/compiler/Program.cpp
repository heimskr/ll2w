#include <atomic>
#include <iostream>
#include <sstream>
#include <thread>

// #define COMPILE_MULTITHREADED
// #define HIDE_PRINTS

#include "compiler/BasicBlock.h"
#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/Parser.h"
#include "parser/StructNode.h"
#include "parser/Values.h"
#include "util/Util.h"
#include "main.h"

// #define SINGLE_FUNCTION "@find_free_block"
// #define SINGLE_FUNCTION "@_ZNKSt3__112basic_stringIwNS_11char_traitsIwEENS_9allocatorIwEEE7compareINS_17basic_string_viewIwS2_EEEENS_9_MetaBaseIXaasr33__can_be_converted_to_string_viewIwS2_T_EE5valuentsr17__is_same_uncvrefISA_S5_EE5valueEE13_EnableIfImplIiEEmmRKSA_mm"
// #define SINGLE_FUNCTION "@_Z8mem_initi"
// #define SINGLE_FUNCTION "@_ZL11alloc_groupim"
// #define SINGLE_FUNCTION "@_ZL10_vsnprintfPFvcPvmmEPcmPKcP13__va_list_tag"
// #define SINGLE_FUNCTION "@_ZN9P0Wrapper6getP4EEPvRm"

namespace LL2W {
	Program::Program(const ASTNode &root) {
		// Look for all struct definitions.
		for (const ASTNode *node: root) {
			if (node->symbol == LLVM_STRUCTDEF) {
				const StructNode *struct_node = dynamic_cast<const StructNode *>(node);
				if (!struct_node)
					throw std::runtime_error("struct_node is null in Program::Program");
				StructType::knownStructs.emplace(*struct_node->name, std::make_shared<StructType>(struct_node));
			}
		}

		for (ASTNode *node: root) {
			if (!node)
				continue;
			switch (node->symbol) {
				case LLVM_FUNCTION_DEF:
					functions.emplace(*node->lexerInfo, new Function(*this, *node));
					break;
				case LLVMTOK_DECLARE: {
					ASTNode *header = node->at(0);
					declarations.emplace(header->lexerInfo->substr(1), dynamic_cast<FunctionHeader *>(header));
					break;
				}
				case LLVMTOK_SOURCE_FILENAME:
					sourceFilename = node->extractName();
					break;
				case LLVM_GLOBAL_DEF:
					if (GlobalVarDef *global = dynamic_cast<GlobalVarDef *>(node)) {
						globals.emplace(*node->lexerInfo, global);
					} else throw std::runtime_error("Node with token GLOBAL_DEF isn't an instance of GlobalVarDef");
					break;
				case LLVMTOK_ATTRIBUTES: {
					AttributesNode *attrnode = dynamic_cast<AttributesNode *>(node);
					fnattrs.emplace(attrnode->index, attrnode->functionAttributes);
					parattrs.emplace(attrnode->index, attrnode->parameterAttributes);
					break;
				}
				case LLVM_ALIAS_DEF:
					aliases.emplace(node->lexerInfo, dynamic_cast<AliasDef *>(node));
					break;
				case LLVMTOK_DIFILE: {
					const int index = node->front()->atoi();
					files.try_emplace(index, node->at(1)->unquote(), node->at(2)->unquote());
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DILOCATION: {
					const int index = node->front()->atoi();
					locations.try_emplace(index, *node->at(1));
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DISUBPROGRAM: {
					const int index = node->front()->atoi();
					subprograms.try_emplace(index, *node->at(1));
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DILB:
				case LLVMTOK_DILBF: {
					const int index = node->front()->atoi();
					lexicalBlocks.try_emplace(index, node->at(2)->atoi(), node->at(1)->atoi());
					highestIndex = std::max(index, highestIndex);
					break;
				}
			}
		}

		for (auto &[index, location]: locations)
			if (subprograms.count(location.scope) != 0)
				location.file = subprograms.at(location.scope).file;
			else if (lexicalBlocks.count(location.scope) != 0) {
				location.file = lexicalBlocks.at(location.scope).file;
				do {
					location.scope = lexicalBlocks.at(location.scope).scope;
				} while (lexicalBlocks.count(location.scope) != 0);
			} else
				warn() << "Couldn't find scope " << location.scope << " from location " << index << ".\n";
	}

	Program::~Program() {
		for (std::pair<const std::string, Function *> &pair: functions)
			delete pair.second;
	}

	void Program::compile() {
#ifdef COMPILE_MULTITHREADED
		std::vector<std::thread> threads;
		threads.reserve(functions.size());

		for (std::pair<const std::string, Function *> &pair: functions) {
			threads.emplace_back(std::thread([&]() {
				pair.second->compile();
			}));
		}

		for (std::thread &thread: threads)
			thread.join();
#else
		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef SINGLE_FUNCTION
			if (*pair.second->name == SINGLE_FUNCTION)
#endif
				pair.second->compile();
		}
#endif
	}

	std::string Program::toString() {
		std::stringstream out;
		out << "#meta\n";
		out << "name: \"" << Util::escape(sourceFilename.empty()? "Program" : sourceFilename) << "\"\n";
		out << "\n#data\n";
		dataSection(out);
		out << "\n#debug\n";
		debugSection(&out);
		out << "\n#code\n\n";
		if (functions.count("@main") == 1 || hasArg("-main"))
			out << ":: main\n<halt>\n\n";
		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef HIDE_PRINTS
			if (pair.first != "@prc" && pair.first != "@prd" && pair.first != "@strprint")
#endif
			out << pair.second->toString() << "\n";
		}
		return out.str();
	}

	void Program::dataSection(std::ostream &out) {
		for (const std::pair<const std::string, GlobalVarDef *> &pair: globals) {
			const std::string name = pair.first.substr(1);
			GlobalVarDef *global = pair.second;
			ConstantPtr constant = global->constant;

			if (global->linkage == Linkage::External)
				continue;

			if (!constant) {
				warn() << name << " inexplicably lacks a constant: " << global->debugExtra() << "\n";
				continue;
			}

			ValuePtr value = constant->value;
			if (value)
				outputNamedValue(out, name, constant, value, global->location);
			else
				out << name << "\n";
		}
	}

	void Program::outputNamedValue(std::ostream &out, const std::string &name, ConstantPtr constant, ValuePtr value,
	                          const ASTLocation &location) {
		ValueType type = value->valueType();
		if (type == ValueType::CString) {
			out << name << ": \"" << dynamic_cast<CStringValue *>(value.get())->reescape() << "\"\n";
		} else if (type == ValueType::Zeroinitializer || type == ValueType::Null) {
			out << name << ": (" << (constant->type->width() / 8) << ")\n";
		} else if (value->isIntLike()) {
			out << name << ": " << value->longValue() << '\n';
		} else if (type == ValueType::Undef) {
			out << name << ": 0\n";
		} else if (type == ValueType::Array) {
			ArrayValue *array = dynamic_cast<ArrayValue *>(value.get());
			out << name << ": ";
			if (array->constants.empty())
				out << "(8)";
			else if (!constant->type)
				throw std::runtime_error("constant->type is null in Program::outputNamedValue");
			else
				outputArray(out, constant->type, *array);
			out << '\n';
		} else if (type == ValueType::Struct) {
			out << name << ": ";
			outputStruct(out, *dynamic_cast<StructValue *>(value.get()));
			out << '\n';
		} else if (type == ValueType::Getelementptr) {
			GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value.get());
			for (const auto &[width, index]: gep->decimals)
				if (!std::holds_alternative<long>(index) || std::get<long>(index) != 0) {
					error() << "Unsupported getelementptr value (invalid indices): " << *gep << '\n';
					return;
				}
			if (gep->variable->valueType() != ValueType::Global)
				error() << "Invalid getelementptrvalue variable: " << *gep->variable << '\n';
			else
				out << name << ": &" << *dynamic_cast<GlobalValue *>(gep->variable.get())->name << '\n';
		} else
			error() << "Unsupported global value: " << *value << " (type: " << static_cast<int>(type) << ") @ "
					<< location << '\n';
	}

	void Program::outputStruct(std::ostream &out, const StructValue &structval, int indentation) {
		const std::string tabs(indentation, '\t');
		out << "{\n";
		for (const ConstantPtr &constant: structval.constants) {
			ConstantPtr converted = constant->convert();
			out << tabs << '\t';
			outputValue(out, converted->type, converted->value, indentation + 1);
			out << '\n';
		}
		out << tabs << "}";
	}

	void Program::outputValue(std::ostream &out, const TypePtr &type, const ValuePtr &value, int indentation) {
		switch (value->valueType()) {
			case ValueType::Array:
				outputArray(out, type, *dynamic_cast<ArrayValue *>(value.get()), indentation);
				break;
			case ValueType::Int:
				out << "#i" << dynamic_cast<IntType *>(type.get())->intWidth << ' '
					<< dynamic_cast<IntValue *>(value.get())->longValue();
					break;
			case ValueType::Null:
			case ValueType::Undef:
				out << "#i8 0";
				break;
			case ValueType::Struct:
				outputStruct(out, *dynamic_cast<StructValue *>(value.get()), indentation);
				break;
			case ValueType::Global:
				out << "&" << *dynamic_cast<GlobalValue *>(value.get())->name;
				break;
			case ValueType::Getelementptr: {
				GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value.get());
				GlobalValue *global = dynamic_cast<GlobalValue *>(gep->variable.get());

				if (!global) {
					std::cerr << *value << '\n';
					std::cerr << *gep->variable << '\n';
					throw std::runtime_error("Expected a global value in getelementptr expression in "
						"Program::outputValue");
				}

				for (const auto &[width, decimal]: gep->decimals)
					if (!std::holds_alternative<long>(decimal) || std::get<long>(decimal) != 0) {
						std::cerr << *value << '\n';
						throw std::runtime_error("Found a non-zero decimal in a getelementptr expression in "
							"Program::outputValue");
					}

				out << "&" << *global->name;
				break;
			}
			default:
				std::cerr << *value << '\n';
				throw std::runtime_error("Unhandled ValueType in Program::outputValue: " +
					value_map.at(value->valueType()));
		}
	}

	void Program::outputType(std::ostream &out, const TypePtr &type) {
		switch (type->typeType()) {
			case TypeType::Array: {
				ArrayType &array = *dynamic_cast<ArrayType *>(type.get());
				out << "(" << array.count << " # ";
				outputType(out, array.subtype);
				out << ")";
				break;
			}
			case TypeType::Int:
				out << "#i" << dynamic_cast<IntType *>(type.get())->intWidth;
				break;
			case TypeType::Pointer:
				outputType(out, dynamic_cast<PointerType *>(type.get())->subtype);
				out << "*";
				break;
			case TypeType::Struct: {
				out << "{";
				bool first = true;
				for (const TypePtr &subtype: dynamic_cast<StructType *>(type.get())->node->types) {
					if (first)
						first = false;
					else
						out << ", ";
					outputType(out, subtype);
				}
				out << "}";
				break;
			}
			case TypeType::Function:
				out << "#fn";
				break;
			default:
				throw std::runtime_error("Unhandled TypeType in Program::outputType: " +
					std::to_string(int(type->typeType())));
		}
	}

	void Program::outputArray(std::ostream &out, const TypePtr &type, const ArrayValue &array, int indentation) {
		outputType(out, type);
		out << " [";
		bool first = true;
		for (const ConstantPtr &constant: array.constants) {
			if (first)
				first = false;
			else
				out << ", ";
			ConstantPtr converted = constant->convert();
			outputValue(out, converted->type, converted->value, indentation);
		}
		out << "]";
	}

	void Program::debugSection(std::ostream * const out) {
		int i = 0;
		for (auto &[index, file]: files) {
			if (out)
				*out << "1 \"" << Util::escape(file.filename) << "\"\n";
			file.index = i++;
		}
		for (auto &[index, subprogram]: subprograms) {
			if (out)
				*out << "2 \"" << Util::escape(subprogram.getName()) << "\"\n";
			subprogram.index = i++;
		}
		for (auto &[index, location]: locations) {
			if (files.count(location.file) == 0) {
				warn() << "Couldn't find file " << location.file << " from location " << index << ".\n";
			} else if (subprograms.count(location.scope) != 0) {
				// TODO: Originally, I had the or'd condition above split into two else if blocks with identical
				// contents, but then I merged them. Were they supposed to be separate with different contents?
				if (out)
					*out << "3 " << files.at(location.file).index << " " << location.line << " " << location.column
					     << " " << subprograms.at(location.scope).index << "\n";
				location.index = i++;
			} else
				warn() << "Couldn't find scope " << location.scope << " from location " << index << ".\n";
		}
	}

	int Program::symbolSize(const std::string &name) const {
		GlobalVarDef *def = globals.at(name);
		if (def->type)
			return def->type->width();
		if (def->constant) {
			if (def->constant->type)
				return def->constant->type->width();
			throw std::runtime_error("Type is null in constant of global " + name);
		}
		throw std::runtime_error("Type and constant are both null for global " + name);
	}

	void Program::debug() {
		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef SINGLE_FUNCTION
			if (*pair.second->name == SINGLE_FUNCTION)
#endif
				pair.second->debug();
		}
	}

	int Program::newDebugIndex() {
		return ++highestIndex;
	}
}