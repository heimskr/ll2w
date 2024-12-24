#pragma once

#include "compiler/BasicType.h"
#include "compiler/CompositeType.h"
#include "compiler/DerivedType.h"
#include "compiler/File.h"
#include "compiler/Function.h"
#include "compiler/LexicalBlock.h"
#include "compiler/LocalVariable.h"
#include "compiler/Location.h"
#include "compiler/Subprogram.h"
#include "compiler/TypeSet.h"
#include "parser/AliasDef.h"
#include "parser/FunctionHeader.h"
#include "util/Lockable.h"

#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

namespace llvm {
	class LLVMContext;
	class Module;
}

namespace LL2W {
	struct ArrayValue;
	class  ASTNode;
	struct StructValue;
	class Value;

	class Program {
		private:
			int64_t highestIndex = -1;
			std::mutex mutex;
			std::mutex analysisMutex;

			void handleSets(const MetadataDef &);
			void handleLists(const MetadataDef &);
			std::string outputStruct(const StructValue &);
			std::string valuePrefix(size_t bitwidth);
			std::string outputValue(const TypePtr &type, const ValuePtr &value);
			std::string outputArray(const ArrayValue &);

		public:
			std::unordered_map<std::string, Function *> functions;
			std::string sourceFilename;
			std::unordered_map<std::string, FunctionHeader *> declarations;
			std::unordered_map<std::string, GlobalVarDef *> globals; // keys include the '@'
			/** A set of all globals to which references were emitted while outputting the data section. Doesn't include
			 *  the '@'. */
			std::unordered_set<std::string> referencedGlobals;
			std::unordered_map<int64_t, std::unordered_set<FnAttr>> fnattrs;
			std::unordered_map<int64_t, std::unordered_set<ParAttr>> parattrs;
			std::unordered_map<const std::string *, AliasDef *> aliases;
			std::unordered_map<int64_t, File> files;
			std::unordered_map<int64_t, Location> locations;
			std::unordered_map<int64_t, Subprogram> subprograms;
			std::unordered_map<const std::string *, int64_t> subprogramIndices;
			std::unordered_map<int64_t, LexicalBlock> lexicalBlocks;
			std::unordered_map<int64_t, LocalVariable> localVariables;
			/** This is a (pointer to a) set of types instead of just one type because of nodes like "!1 = {!2, !3}". */
			std::unordered_map<int64_t, std::shared_ptr<TypeSet>> basicTypeSets;
			std::unordered_map<int64_t, std::vector<std::shared_ptr<LLVMType>>> basicTypeLists;
			std::unordered_map<int64_t, int64_t> subroutineTypes;
			std::unordered_map<int64_t, std::shared_ptr<DerivedType>> derivedTypes;
			std::unordered_map<int64_t, std::shared_ptr<CompositeType>> compositeTypes;
			/** A set of all LLVM debug indices found in the program. */
			std::unordered_set<int64_t> debugIndices;
			/** A map of names of functions that do nothing except return an argument to the index of the argument they
			 *  return. Names don't contain a leading @. */
			std::unordered_map<std::string, int64_t> simpleFunctions;
			/** A set of names of functions that do nothing but return void. Names don't contain a leading @. */
			std::unordered_set<std::string> uselessFunctions;
			/** A map of names of functions that do nothing but return a constant to the constant they return.
			 *  Names don't contain a leading @. */
			std::unordered_map<std::string, std::shared_ptr<Value>> constantReturningFunctions;
			std::unique_ptr<llvm::Module> llvmModule;
			Lockable<std::unordered_map<const std::string *, std::string>> renderedFunctions;

			Program(std::string_view, llvm::LLVMContext &);
			Program(const ASTNode &);

			~Program();

			/** Populates simpleFunctions. */
			void analyze();

			/** Compiles all the functions in the program. */
			void compile();

			/** Returns the source code of the program. */
			std::string toString();

			/** Outputs the data section (excluding the #data header) to a stream. */
			void dataSection(std::ostream &);

			/** Outputs the debug data section (excluding the #debug header) to a stream. */
			void debugSection(std::ostream *);

			/** Returns the size (in bits) of the global variable with a given name.
			 *  The name should include an initial "@". */
			int symbolSize(const std::string &) const;

			/** Prints debug information for all the functions in the program. */
			void debug();

			int newDebugIndex();

			std::unique_lock<std::mutex> getLock() { return std::unique_lock(mutex); }
	};
}
