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
// #define SINGLE_FUNCTION "@_ZNKSt3__117basic_string_viewIwNS_11char_traitsIwEEE4sizeEv"
// #define SINGLE_FUNCTION "@_ZNSt3__112basic_stringIwNS_11char_traitsIwEENS_9allocatorIwEEE17__assign_no_aliasILb1EEERS5_PKwm"
// #define SINGLE_FUNCTION "@_ZL8_out_revPFvcPvmmEPcmmPKcmjj"
// #define SINGLE_FUNCTION "@_ZL9_is_digitc"
// #define SINGLE_FUNCTION "@_ZL10_vsnprintfPFvcPvmmEPcmPKcS_"
// #define SINGLE_FUNCTION "@memcpy"

namespace LL2W {
	struct GlobalData {
		ConstantPtr constant;
		ValuePtr value;
		ASTLocation location;
		GlobalData(const ConstantPtr &constant_, const ValuePtr &value_, const ASTLocation &location_):
			constant(constant_), value(value_), location(location_) {}
	};

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
		out << "\n#text\n\n%data\n\n";
		dataSection(out);
		out << "\n%code\n\n";
		if (functions.count("@main") == 1 || hasArg("-main"))
			out << ":: main\n<halt>\n\n";
		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef HIDE_PRINTS
			if (pair.first != "@prc" && pair.first != "@prd" && pair.first != "@strprint")
#endif
			out << pair.second->toString() << "\n";
		}
		const std::string declarations = getDeclarations();
		if (!declarations.empty())
			out << "\n" << declarations << "\n";
		out << "\n#debug\n";
		debugSection(&out);
		return out.str();
	}

	std::string Program::getDeclarations() const {
		std::string out;
		bool first = true;
		std::set<std::string> function_labels;

		for (const auto &[name, function]: functions)
			function_labels.insert(function->labels.cbegin(), function->labels.cend());

		for (const std::string &label: referencedGlobals)
			if (emittedGlobals.count(label) == 0 && function_labels.count(label) == 0) {
				if (first)
					first = false;
				else
					out += '\n';
				// out += "%type " +
			}
		return out;
	}

	void Program::dataSection(std::ostream &out) {
		std::map<std::string, GlobalData> global_data;
		std::map<std::string, std::string> global_strings;

		for (const std::pair<const std::string, GlobalVarDef *> &pair: globals) {
			const std::string name = pair.first.substr(1);
			GlobalVarDef *global = pair.second;

			if (global->linkage == Linkage::External)
				continue;

			ConstantPtr constant = global->constant;

			if (!constant) {
				warn() << name << " inexplicably lacks a constant: " << global->debugExtra() << "\n";
				continue;
			}

			constant = constant->convert();
			global_data.try_emplace(name, constant, constant->value, global->location);
		}

		bool changed;

		do {
			changed = false;
			for (const auto &[name, data]: global_data) {
				if (data.value) {
					const std::string stringified = stringifyNamedValue(data.constant, data.value, data.location);
					if (!stringified.empty()) {
						global_strings.emplace(name, stringified);
						changed = true;
					} else if (data.value->valueType() == ValueType::Global) {
						const std::string &target = *dynamic_cast<GlobalValue *>(data.value.get())->name;
						if (global_strings.count(target) != 0) {
							global_strings.emplace(name, global_strings.at(target));
							changed = true;
						}
					}
				} else {
					global_strings.emplace(name, "");
					changed = true;
				}

				if (changed) {
					global_data.erase(name);
					break;
				}
			}
		} while (changed);

		emittedGlobals.clear();
		for (const auto &[name, stringified]: global_strings) {
			emittedGlobals.insert(name);
			if (stringified.empty())
				out << '@' << name << "\n%8b 0\n\n";
			else
				out << '@' << name << '\n' << stringified << "\n\n";
		}

		if (!global_data.empty()) {
			error() << "Couldn't translate global constants (is there a loop?):\n";
			for (const auto &[name, data]: global_data)
				std::cerr << "- " << name << " @ " << data.location;
			throw std::runtime_error("Global constant translation failed");
		}
	}

	std::string Program::stringifyNamedValue(ConstantPtr constant, ValuePtr value, const ASTLocation &location) {
		ValueType type = value->valueType();
		if (type == ValueType::CString) {
			return "%string \"" + dynamic_cast<CStringValue *>(value.get())->reescape() + "\"";
		} else if (type == ValueType::Zeroinitializer || type == ValueType::Null || type == ValueType::Undef) {
			return "%fill " + std::to_string(constant->type->width() / 8) + " 0";
		} else if (value->isIntLike()) {
			return valuePrefix(constant->type->width()) + std::to_string(value->longValue());
		} else if (type == ValueType::Array) {
			ArrayValue *array = dynamic_cast<ArrayValue *>(value.get());
			std::string out;
			if (array->constants.empty())
				out += "%8b 0";
			else if (!constant->type)
				throw std::runtime_error("constant->type is null in Program::stringifyNamedValue");
			else
				out += outputArray(*array);
			return out;
		} else if (type == ValueType::Struct) {
			return outputStruct(*dynamic_cast<StructValue *>(value.get()));
		} else if (type == ValueType::Getelementptr) {
			GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value.get());
			for (const auto &[width, index]: gep->decimals)
				if (!std::holds_alternative<long>(index) || std::get<long>(index) != 0) {
					error() << "Unsupported getelementptr value (invalid indices): " << *gep << '\n';
					return {};
				}
			if (gep->variable->valueType() != ValueType::Global)
				error() << "Invalid getelementptrvalue variable: " << *gep->variable << '\n';
			else
				return '&' + *dynamic_cast<GlobalValue *>(gep->variable.get())->name;
		} else if (type == ValueType::Global) {
			referencedGlobals.insert(*dynamic_cast<GlobalValue *>(value.get())->name);
			// Return an empty string to indicate that the value isn't valid yet, but don't print any error.
			return {};
		} else
			error() << "Unsupported global value: " << *value << " (type: " << int(type) << ") @ "
					<< location << '\n';
		return {};
	}

	std::string Program::outputStruct(const StructValue &structval) {
		std::string out;
		bool first = true;
		for (const ConstantPtr &constant: structval.constants) {
			ConstantPtr converted = constant->convert();
			if (first)
				first = false;
			else
				out += '\n';
			out += outputValue(converted->type, converted->value);
		}
		return out;
	}

	std::string Program::valuePrefix(size_t bitwidth) {
		if (bitwidth % 8 != 0)
			throw std::runtime_error("Int width (" + std::to_string(bitwidth) + "b) isn't a multiple of 8");
		switch (bitwidth / 8) {
			case 8: return "%8b ";
			case 4: return "%4b ";
			case 2: return "%2b ";
			case 1: return "%1b ";
			default:
				throw std::runtime_error("Invalid int width: " + std::to_string(bitwidth / 8) + "B");
		}
	}

	std::string Program::outputValue(const TypePtr &type, const ValuePtr &value) {
		switch (value->valueType()) {
			case ValueType::Array:
				return outputArray(*dynamic_cast<ArrayValue *>(value.get()));
			case ValueType::Int: {
				const auto int_width = dynamic_cast<IntType *>(type.get())->intWidth;
				const std::string stringified = std::to_string(dynamic_cast<IntValue *>(value.get())->longValue());
				return valuePrefix(int_width) + stringified;
			}
			case ValueType::Null:
			case ValueType::Undef:
				if (type)
					return valuePrefix(type->width()) + "0";
				return "%1b 0";
			case ValueType::Struct:
				return outputStruct(*dynamic_cast<StructValue *>(value.get()));
			case ValueType::Global: {
				const std::string *name = dynamic_cast<GlobalValue *>(value.get())->name;
				referencedGlobals.insert(*name);
				return "%8b " + *name;
			}
			case ValueType::Getelementptr: {
				GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value.get());
				GlobalValue *global;

				auto validate = [value](GetelementptrValue *gep) {
					for (const auto &[width, decimal]: gep->decimals)
						if (!std::holds_alternative<long>(decimal) || std::get<long>(decimal) != 0) {
							std::cerr << *value << '\n';
							throw std::runtime_error("Found a non-zero decimal in a getelementptr expression in "
								"Program::outputValue");
						}
				};

				while (gep) {
					global = dynamic_cast<GlobalValue *>(gep->variable.get());

					if (!global) {
						if (GetelementptrValue *subgep = dynamic_cast<GetelementptrValue *>(gep->variable.get())) {
							validate(gep);
							gep = subgep;
							continue;
						}

						std::cerr << *value << '\n';
						std::cerr << *gep->variable << '\n';
						throw std::runtime_error("Expected a global value in getelementptr expression in "
							"Program::outputValue");
					}

					validate(gep);
				}

				return '&' + *global->name;
			}
			default:
				std::cerr << *value << '\n';
				throw std::runtime_error("Unhandled ValueType in Program::outputValue: " +
					value_map.at(value->valueType()));
		}
	}

	std::string Program::outputArray(const ArrayValue &array) {
		std::string out;
		bool first = true;
		for (const ConstantPtr &constant: array.constants) {
			if (first)
				first = false;
			else
				out += "\n";
			ConstantPtr converted = constant->convert();
			out += outputValue(converted->type, converted->value);
		}
		return out;
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
