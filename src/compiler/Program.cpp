// #define ANALYZE_MULTITHREADED
#define COMPILE_MULTITHREADED
// #define HIDE_PRINTS
// #define GRADUAL_CODE_PRINTING
#define DEBUG_SINGLE_FUNCTION

// #define SINGLE_FUNCTION "@\"_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEE6_M_runEv\""
// #define SINGLE_FUNCTION "kernel_main"
// #define SINGLE_FUNCTION "@_ZL21update_offset_to_basePKcl"
// #define SINGLE_FUNCTION "_ZL10_vsnprintfPFvcPvmmEPcmPKcS_"
// #define SINGLE_FUNCTION "_ZN5Timer5queueElRKNSt3__18functionIFvvEEE"
// #define SINGLE_FUNCTION "_GLOBAL__sub_I_Instructions.cpp"
// #define SINGLE_FUNCTION "_Z3prcc"
// #define SINGLE_FUNCTION "_ZN5Wasmc12BinaryParser15applyRelocationEmm"
// #define SINGLE_FUNCTION "_ZN6Kernel12startProcessEPKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE"
// #define SINGLE_FUNCTION "_ZN6Kernel6panicfEPKcz"
// #define SINGLE_FUNCTION "_ZNKSt3__110__function6__funcIZZN8Thurisaz11addCommandsERNS_3mapINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS2_7CommandENS_4lessIS9_EENS7_INS_4pairIKS9_SA_EEEEEEENK4$_31clERNS2_7ContextERKNS_6vectorIS9_NS7_IS9_EEEEEUlvE1_NS7_ISR_EEFvvEE7__cloneEPNS0_6__baseIST_EE"
// #define SINGLE_FUNCTION "__cxx_global_var_init.118"
// #define SINGLE_FUNCTION "_ZN6Kernel4loopEv"
// #define SINGLE_FUNCTION "_ZL11_out_buffercPvmm"
// #define SINGLE_FUNCTION "fctprintf"
// #define SINGLE_FUNCTION "_ZN5Wasmc7Section7combineESt16initializer_listINSt3__117reference_wrapperIS0_EEE"
// #define SINGLE_FUNCTION "_ZNSt3__13mapIl11ProcessDataNS_4lessIlEENS_9allocatorINS_4pairIKlS1_EEEEE11try_emplaceIJRlRPA256_mRmN6Paging6TablesERPvRKmEEENS5_INS_14__map_iteratorINS_15__tree_iteratorINS_12__value_typeIlS1_EEPNS_11__tree_nodeISP_SI_EElEEEEbEERS6_DpOT_"
// #define SINGLE_FUNCTION "strprint"
// #define SINGLE_FUNCTION "_ZN8MBREntry5debugEv"
// #define SINGLE_FUNCTION "_ZN6Paging6Tables5resetEb"
// #define SINGLE_FUNCTION "_ZNSt3__14pairIKNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEN8Thurisaz7CommandEEC2IRA5_KcRS9_TnNS_9enable_ifIXclsr10_CheckArgsE17__enable_implicitIT_T0_EEEbE4typeELb0EEEOSH_OSI_"
// #define SINGLE_FUNCTION "vsnprintf_"
// #define SINGLE_FUNCTION "__cxx_global_var_init.4"
// #define SINGLE_FUNCTION "printf"
// #define SINGLE_FUNCTION "isupper"
// #define SINGLE_FUNCTION "_ZL12_ntoa_formatPFvcPvmmEPcmmS2_mbjjjj"
// #define SINGLE_FUNCTION "_ZN6Kernel5mountERKNSt3__112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEENS0_10shared_ptrIN2FS6DriverEEE"
// #define SINGLE_FUNCTION "_ZN5Wasmc12BinaryParser5parseEv"
// #define SINGLE_FUNCTION "_ZN8Thurisaz11addCommandsERNSt3__13mapINS0_12basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEENS_7CommandENS0_4lessIS7_EENS5_INS0_4pairIKS7_S8_EEEEEE"
// #define SINGLE_FUNCTION "_ZN6Paging6Tables7initPMMEv"
// #define SINGLE_FUNCTION "_ZN6Paging6Tables6assignEPA256_mlhhhhhhPvh"

#ifdef SINGLE_FUNCTION
#undef COMPILE_MULTITHREADED
#endif

#include "allocator/ColoringAllocator.h"
#include "compiler/BasicBlock.h"
#include "compiler/BasicType.h"
#include "compiler/Getelementptr.h"
#include "compiler/PaddedStructs.h"
#include "compiler/Program.h"
#include "parser/ASTNode.h"
#include "parser/Parser.h"
#include "parser/StructNode.h"
#include "parser/Values.h"
#include "util/ThreadPool.h"
#include "util/Timer.h"
#include "util/Util.h"
#include "util/Waiter.h"

#include <llvm/AsmParser/LLParser.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SmallVectorMemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

#include "main.h"
#include <atomic>
#include <format>
#include <iostream>
#include <mutex>
#include <print>
#include <sstream>
#include <syncstream>
#include <thread>

namespace {
#if defined(ANALYZE_MULTITHREADED) || defined(COMPILE_MULTITHREADED)
	constexpr size_t PARALLELISM = 24;
#endif

#if defined(GRADUAL_CODE_PRINTING) && defined(COMPILE_MULTITHREADED) && !defined(SINGLE_FUNCTION)
	std::mutex gradualCodePrintingMutex;
#endif
}

namespace LL2W {
	struct GlobalData {
		ConstantPtr constant;
		ValuePtr value;
		TypePtr type;
		ASTLocation location;
		GlobalData(ConstantPtr constant, ValuePtr value, TypePtr type, ASTLocation location):
			constant(std::move(constant)),
			value(std::move(value)),
			type(std::move(type)),
			location(std::move(location)) {}
	};

	Program::Program(std::string_view source_code, llvm::LLVMContext &context) {
		llvm::SMDiagnostic err;
		llvm::SmallVector<char> vector(source_code.begin(), source_code.end());
		llvmModule = llvm::getLazyIRModule(std::make_unique<llvm::SmallVectorMemoryBuffer>(std::move(vector)), err, context);
		assert(llvmModule != nullptr);

		for (llvm::StructType *llvm_struct: llvmModule->getIdentifiedStructTypes()) {
			StructType::knownStructs.emplace(llvm_struct->getName(), std::make_shared<StructType>(*llvm_struct));
		}

		for (const auto &symbol: llvmModule->getValueSymbolTable()) {
			llvm::Value *value = symbol.getValue();

			if (auto *var = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
				globals.emplace('@' + symbol.getKey().str(), new GlobalVarDef(*var)); // TODO: memleak
				continue;
			}

			if (auto *alias = llvm::dyn_cast<llvm::GlobalAlias>(value)) {
				aliases.emplace(StringSet::intern('@' + symbol.getKey().str()), new AliasDef(*alias));
				continue;
			}

			if (auto *function = llvm::dyn_cast<llvm::Function>(value)) {
				declarations.emplace('@' + symbol.getKey().str(), new FunctionHeader(*function));
				continue;
			}

			warn() << "Symbol type: " << value->getValueID() << "\n";
		}

		info() << "Creating functions.\n";
		for (llvm::Function &function: *llvmModule) {
			if (function.getInstructionCount() > 0) {
				functions.emplace(function.getName().str(), new Function(*this, &function)); // TODO: memleak
			}
		}
	}

	Program::Program(const ASTNode &root) {
		// Look for all struct definitions.
		StructType::knownStructs.clear();
		for (const ASTNode *node: root) {
			if (node->symbol == LLVM_STRUCTDEF) {
				const StructNode *struct_node = dynamic_cast<const StructNode *>(node);
				if (!struct_node) {
					throw std::runtime_error("struct_node is null in Program::Program");
				}
				StructType::knownStructs.emplace(*struct_node->name, std::make_shared<StructType>(struct_node));
			}
		}

		for (ASTNode *node: root) {
			if (node == nullptr) {
				continue;
			}

			switch (node->symbol) {
				case LLVM_FUNCTION_DEF:
					functions.emplace(*node->lexerInfo, new Function(*this, *node));
					break;
				case LLVMTOK_DECLARE: {
					ASTNode *header_node = node->front();
					auto *header = dynamic_cast<FunctionHeader *>(header_node);
					if (header->debugIndex == -1 && 1 < node->size()) {
						header->debugIndex = node->at(1)->front()->atoi();
					}
					declarations.emplace(header->lexerInfo->substr(1), header);
					break;
				}
				case LLVMTOK_SOURCE_FILENAME:
					sourceFilename = node->extractName();
					break;
				case LLVM_GLOBAL_DEF:
					if (GlobalVarDef *global = dynamic_cast<GlobalVarDef *>(node)) {
						globals.emplace(*node->lexerInfo, global);
					} else {
						throw std::runtime_error("Node with token GLOBAL_DEF isn't an instance of GlobalVarDef");
					}
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
					const auto index = node->front()->atoi();
					files.try_emplace(index, node->at(1)->unquote(), node->at(2)->unquote());
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DILOCATION: {
					const auto index = node->front()->atoi();
					locations.try_emplace(index, *node->at(1));
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DISUBPROGRAM: {
					const auto index = node->front()->atoi();
					subprograms.try_emplace(index, *node->at(1));
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DILB:
				case LLVMTOK_DILBF: {
					const auto index = node->front()->atoi();
					lexicalBlocks.try_emplace(index, node->at(2)->atoi(), node->at(1)->atoi());
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DILV: {
					const auto index = node->front()->atoi();
					localVariables.try_emplace(index, *node);
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DIBT: {
					const auto index = node->front()->atoi();
					basicTypeSets.try_emplace(index, std::make_shared<TypeSet>(TypeSet{
						std::make_shared<BasicType>(*node)
					}));
					basicTypeLists.try_emplace(index, std::vector<std::shared_ptr<LLVMType>>{
						std::make_shared<BasicType>(*node)
					});
					highestIndex = std::max(index, highestIndex);
					break;
				}
				case LLVMTOK_DIST: {
					const auto index = node->front()->atoi();
					for (const ASTNode *subnode: *node->back()) {
						if (subnode->symbol == LLVMTOK_TYPES) {
							const auto subindex = subnode->front()->atoi();
							subroutineTypes.emplace(index, subindex);
							break;
						}
					}
					break;
				}
				case LLVMTOK_DIDT: {
					const auto index = node->front()->atoi();
					derivedTypes.try_emplace(index, std::make_shared<DerivedType>(*node));
					break;
				}
				case LLVMTOK_DICT: {
					const auto index = node->front()->atoi();
					compositeTypes.try_emplace(index, std::make_shared<CompositeType>(*node));
					break;
				}
			}
		}

		// If we have a line like "!3 = !{!1, !2}" and the list contains any BasicTypes, add each BasicType in the list
		// to !3's set of BasicTypes. Note that this won't work recursively in all instances.
		for (auto iter = root.rbegin(), rend = root.rend(); iter != rend; ++iter) {
			if (auto *def = dynamic_cast<MetadataDef *>(*iter)) {
				handleSets(*def);
			}
		}

		for (ASTNode *node: root) {
			if (auto *def = dynamic_cast<MetadataDef *>(node)) {
				handleSets(*def);
			}
		}

		for (ASTNode *node: root) {
			if (auto *def = dynamic_cast<MetadataDef *>(node)) {
				handleLists(*def);
			}
		}

		for (auto &[index, location]: locations) {
			if (subprograms.count(location.scope) != 0) {
				location.file = subprograms.at(location.scope).file;
			} else if (lexicalBlocks.count(location.scope) != 0) {
				location.file = lexicalBlocks.at(location.scope).file;
				do {
					location.scope = lexicalBlocks.at(location.scope).scope;
				} while (lexicalBlocks.count(location.scope) != 0);
			} else {
				warn() << "Couldn't find scope " << location.scope << " from location " << index << ".\n";
			}
		}
	}

	Program::~Program() {
		for (const auto &[fname, function]: functions)
			delete function;
	}

	void Program::handleSets(const MetadataDef &def) {
		if (Util::isNumeric(std::string_view(*def.front()->lexerInfo).substr(1))) {
			static const std::string *nullstr = StringSet::intern("null");
			const auto index = def.front()->atoi();
			for (ASTNode *subnode: *def.back()) {
				if (subnode->symbol == LLVMTOK_METABANG && subnode->lexerInfo != nullstr) {
					const int64_t subindex = subnode->atoi();
					if (basicTypeSets.contains(subindex)) {
						if (!basicTypeSets.contains(index)) {
							basicTypeSets.emplace(index, std::make_shared<TypeSet>());
						}
						for (const auto &basic_type: *basicTypeSets.at(subindex)) {
							basicTypeSets[index]->insert(basic_type);
						}
					}
				}
			}
		}
	}

	void Program::handleLists(const MetadataDef &def) {
		if (Util::isNumeric(std::string_view(*def.front()->lexerInfo).substr(1))) {
			static const std::string *nullstr = StringSet::intern("null");
			const auto index = def.front()->atoi();
			// info() << index << ':';
			for (ASTNode *subnode: *def.back()) {
				// std::cerr << ' ' << *subnode->lexerInfo;
				if (subnode->lexerInfo == nullstr) {
					basicTypeLists[index].push_back(nullptr);
				} else if (subnode->symbol == LLVMTOK_METABANG) {
					try {
						const int64_t subindex = subnode->atoi();
						if (basicTypeSets.contains(subindex)) {
							const auto &typeset = basicTypeSets.at(subindex);
							if (typeset->size() != 1) {
								error() << "Typeset " << subindex << " has a size of " << typeset->size() << '\n';
							} else {
								basicTypeLists[index].push_back(*typeset->begin());
							}
						} else if (derivedTypes.contains(subindex)) {
							basicTypeLists[index].push_back(derivedTypes.at(subindex));
						} else if (compositeTypes.contains(subindex)) {
							basicTypeLists[index].push_back(compositeTypes.at(subindex));
						} else {
							// std::cerr << "\e[2m(\e[2;31mNF\e[39;2m)\e[22m";
							// error() << "Typeset " << subindex << " not found\n";
							// subnode->debug();
						}
					} catch (const std::invalid_argument &) {}
				}
			}
			// std::cerr << '\n';
		}
	}

	void Program::analyze() {
		info() << "Analyzing program.\n";
		Timer timer{"ProgramAnalysis"};

		auto run = [this](const std::string &name, Function *function) {
			ValuePtr value;
			long simple_index = -1;
			const Function::Type analysis = function->analyze(&value, &simple_index);
			std::unique_lock lock(analysisMutex);
			switch (analysis) {
				case Function::Type::Simple:
					simpleFunctions.emplace(name.substr(1), simple_index);
					break;
				case Function::Type::Useless:
					uselessFunctions.insert(name.substr(1));
					break;
				case Function::Type::Constant:
					constantReturningFunctions.emplace(name.substr(1), value);
					break;
				default:
					break;
			}
		};

#ifdef ANALYZE_MULTITHREADED
		ThreadPool pool(PARALLELISM);
		pool.start();
		Waiter waiter(functions.size());

		for (auto &[name, function]: functions) {
			pool.add([&waiter, &run, &name, function](ThreadPool &, size_t) {
				run(name, function);
				if (auto remaining = waiter--; remaining % 10 == 0) {
					info() << "Remaining: " << remaining << "\n";
				}
			});
		}

		waiter.wait();
		pool.join();
#else
		for (auto &[name, function]: functions) {
			run(name, function);
		}
#endif

		info() << "Analysis complete.\n";

		timer.stop();
		// Timer::summary();
		Timer::clear();
	}

	void Program::compile() {
		info() << "Compiling program.\n";
		Timer timer{"ProgramCompilation"};

#ifdef COMPILE_MULTITHREADED
		ThreadPool pool(PARALLELISM);
		pool.start();
		Waiter waiter(functions.size());

		for (auto &[name, function]: functions) {
			pool.add([&](ThreadPool &, size_t) {
				// info() << "Compiling " << *function->name << " ...\n";
				function->compile();
#ifdef GRADUAL_CODE_PRINTING
				std::unique_lock lock(gradualCodePrintingMutex);
				std::cerr << function->toString() << std::endl;
				lock.unlock();
#endif
				auto remaining = waiter--;
				if (remaining % 100 == 0 || (remaining < 100 && remaining % 10 == 0) || remaining < 10) {
					info() << "Remaining: " << remaining << "\n";
				}
			});
		}

		waiter.wait();
		pool.join();
#else
		for (auto &[name, function]: functions) {
#ifdef SINGLE_FUNCTION
			if (*function->name == "@" SINGLE_FUNCTION) {
#endif
				info() << "Compiling " << *function->name << " ...\n";
				function->compile();

#ifdef SINGLE_FUNCTION
#ifdef DEBUG_SINGLE_FUNCTION
				function->debug();
				// dynamic_cast<ColoringAllocator &>(*function->allocator).interference.renderTo("final_interference.svg");
#endif
			}
#elif defined(GRADUAL_CODE_PRINTING)
				std::cout << function->toString() << std::endl;
#endif
		}
#endif

		info() << "Compilation complete.\n";
		timer.stop();
		Timer::summary();
		Timer::clear();
	}

	std::string Program::toString() {
		std::stringstream out;
		out << "#meta\n";
		out << "name: \"" << Util::escape(sourceFilename.empty()? "Program" : sourceFilename) << "\"\n";

		out << "\n#debug\n";
		debugSection(&out);

		out << "\n#text\n\n%data\n\n";
		dataSection(out);

		out << "\n%code\n\n";
		if (functions.count("@main") == 1 || hasArg("-main")) {
			out << ":: main\n<halt>\n\n";
		}

		for (std::pair<const std::string, Function *> &pair: functions) {
#ifdef SINGLE_FUNCTION
			if (pair.first == SINGLE_FUNCTION)
#endif
#ifdef HIDE_PRINTS
			if (pair.first != "@prc" && pair.first != "@prd" && pair.first != "@strprint")
#endif
			out << pair.second->toString() << "\n";
		}

		return out.str();
	}

	void Program::dataSection(std::ostream &out) {
		std::map<std::string, GlobalData> global_data;
		std::map<std::string, std::string> global_strings;

		for (const std::pair<const std::string, GlobalVarDef *> &pair: globals) {
			const std::string &name = pair.first;
			GlobalVarDef *global = pair.second;
			ConstantPtr constant = global->constant;

			if (!constant) {
				warn() << name << " inexplicably lacks a constant: " << global->debugExtra() << "\n";
				continue;
			}

			constant = constant->convert();
			global_data.try_emplace(name, constant, constant->value, global->type, global->location);
		}

		if (auto iter = global_data.find("@llvm.global_ctors"); iter != global_data.end()) {
			const GlobalData &def = iter->second;
			if (auto *array = dynamic_cast<const ArrayType *>(def.type.get())) {
				out << "%align 8\n\n@__ctors_start\n%8b llvm.global_ctors\n\n";
				out << "@__ctors_end\n%8b llvm.global_ctors + " << (24 * array->count) << "\n\n";
			} else if (!def.type) {
				throw std::runtime_error("@llvm.global_ctors was expected to be an array but has no type");
			} else {
				throw std::runtime_error("@llvm.global_ctors was expected to be an array but is " + def.type->toString());
			}
		}

		bool changed{};

		do {
			changed = false;
			for (const auto &[name, data]: global_data) {
				if (data.value) {
					std::string stringified = outputValue(data.type, data.value);
					if (!stringified.empty()) {
						global_strings.emplace(name, std::move(stringified));
						changed = true;
					} else if (data.value->valueType() == ValueType::Global) {
						const std::string &target = *dynamic_cast<GlobalValue *>(data.value.get())->name;
						if (global_strings.contains(target)) {
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

		for (const auto &[name, stringified]: global_strings) {
			out << "%align 8\n";
			if (stringified.empty()) {
				out << name << "\n%8b 0\n\n";
			} else {
				out << name << '\n' << stringified << "\n\n";
			}
		}

		if (!global_data.empty()) {
			error() << "Couldn't translate global constants (is there a loop?):\n";
			for (const auto &[name, data]: global_data) {
				std::println(std::cerr, "- {} @ {}", name, std::string(data.location));
			}
			throw std::runtime_error("Global constant translation failed");
		}
	}

	std::string Program::outputStruct(std::shared_ptr<StructType> struct_type, const StructValue &structval) {
		std::string out;
		bool first = true;
		const bool packed = structval.packed;

		std::vector<ConstantPtr> constants;
		std::vector<TypePtr> types;

		for (const ConstantPtr &constant: structval.constants) {
			constants.push_back(constant->convert());
			types.push_back(constants.back()->type);
		}

		if (packed) {
			for (const ConstantPtr &constant: constants) {
				if (first) {
					first = false;
				} else {
					out += '\n';
				}
				out += outputValue(constant->type, constant->value);
			}
		} else {
			// auto snode = std::make_shared<StructNode>(types, StructShape::Default);
			// snode->name = structval.
			// auto stype = std::make_shared<StructType>(snode);
			int sum = 0, i = 0;
			for (const ConstantPtr &constant: constants) {
				if (first) {
					first = false;
				} else {
					out += '\n';
				}
				const int offset = PaddedStructs::getOffset(struct_type, i++) / 8;
				const int difference = offset - sum;
				if (difference < 0) {
					throw std::runtime_error("Difference between struct offset and total width is negative");
				} else if (0 < difference) {
					out += "%fill " + std::to_string(difference) + " 0\n";
					sum = offset;
				}
				out += outputValue(constant->type, constant->value);
				sum += constant->type->width() / 8;
			}
		}

		return out;
	}

	std::string Program::valuePrefix(size_t bitwidth) {
		if (bitwidth % 8 != 0) {
			throw std::runtime_error("Int width (" + std::to_string(bitwidth) + "b) isn't a multiple of 8");
		}

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
			case ValueType::CString:
				return "%stringz \"" + dynamic_cast<CStringValue *>(value.get())->reescape() + '"';

			case ValueType::Array:
				return outputArray(dynamic_cast<ArrayValue &>(*value.get()));

			case ValueType::Int: {
				const auto int_width = dynamic_cast<IntType *>(type.get())->bitWidth;
				const std::string stringified = std::to_string(dynamic_cast<IntValue *>(value.get())->longValue());
				return valuePrefix(int_width) + stringified;
			}

			case ValueType::Null:
			case ValueType::Undef:
			case ValueType::Zeroinitializer:
				if (type) {
					const auto width = type->width();
					if (width % 8) {
						throw std::runtime_error("Invalid type width for null/undef/zeroinitializer value: " + std::to_string(width) + 'b');
					}
					return "%fill " + std::to_string(width / 8) + " 0";
				}
				return "%1b 0";

			case ValueType::Struct:
				return outputStruct(std::dynamic_pointer_cast<StructType>(type), dynamic_cast<StructValue &>(*value));

			case ValueType::Global: {
				const std::string *name = dynamic_cast<GlobalValue *>(value.get())->name;
				referencedGlobals.insert(*name);
				return "%8b " + name->substr(1);
			}

			case ValueType::Getelementptr: {
				GetelementptrValue *gep = dynamic_cast<GetelementptrValue *>(value.get());

				auto validate = [value](GetelementptrValue *gep) {
					for (const auto &[width, decimal]: gep->decimals) {
						if (!std::holds_alternative<long>(decimal)) {
							std::cerr << *value << '\n';
							throw std::runtime_error("Found an invalid decimal in a getelementptr expression in Program::outputValue");
						}
					}
				};

				validate(gep);
				long offset = Getelementptr::compute(gep, nullptr) / 8;
				std::string comment = " // Offsets: " + std::to_string(offset);
				bool comment_changed = false;

				while (gep->variable->valueType() == ValueType::Getelementptr) {
					gep = dynamic_cast<GetelementptrValue *>(gep->variable.get());
					validate(gep);
					const long new_offset = Getelementptr::compute(gep, nullptr) / 8;
					comment += ", " + std::to_string(new_offset);
					comment_changed = true;
					offset += new_offset;
				}

				if (gep->variable->valueType() != ValueType::Global) {
					throw std::runtime_error("Expected source of a getelementptr expression to be a global, but got type " + value_map.at(gep->variable->valueType()) + " instead");
				}

				return "%8b " + dynamic_cast<GlobalValue &>(*gep->variable).name->substr(1) + " + " + std::to_string(offset) + (comment_changed? comment : "");
			}

			default:
				std::cerr << *value << '\n';
				throw std::runtime_error("Unhandled ValueType in Program::outputValue: " + value_map.at(value->valueType()));
		}
	}

	std::string Program::outputArray(const ArrayValue &array) {
		std::string out;
		bool first = true;
		for (const ConstantPtr &constant: array.constants) {
			if (first) {
				first = false;
			} else {
				out += '\n';
			}
			ConstantPtr converted = constant->convert();
			out += outputValue(converted->type, converted->value);
		}
		return out;
	}

	void Program::debugSection(std::ostream *out) {
		int i = 0;
		for (auto &[index, file]: files) {
			if (out) {
				*out << "1 \"" << Util::escape(file.filename) << "\"\n";
			}
			file.index = i++;
		}
		for (auto &[index, subprogram]: subprograms) {
			if (out) {
				*out << "2 \"" << Util::escape(subprogram.getName()) << "\"\n";
			}
			subprogram.index = i++;
		}
		for (auto &[index, location]: locations) {
			if (files.count(location.file) == 0) {
				warn() << "Couldn't find file " << location.file << " from location " << index << ".\n";
			} else if (subprograms.count(location.scope) != 0) {
				if (out) {
					*out << "3 " << files.at(location.file).index << ' ' << location.line << ' ' << location.column
					     << ' ' << subprograms.at(location.scope).index << "\n";
				}
				location.index = i++;
			} else {
				warn() << "Couldn't find scope " << location.scope << " from location " << index << ".\n";
			}
		}
	}

	int Program::symbolSize(const std::string &name) const {
		GlobalVarDef *def = globals.at(name);

		if (def->type) {
			return def->type->width();
		}

		if (def->constant) {
			if (def->constant->type) {
				return def->constant->type->width();
			}
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
