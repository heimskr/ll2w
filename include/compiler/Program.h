#pragma once

#include <list>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "compiler/File.h"
#include "compiler/Function.h"
#include "compiler/LexicalBlock.h"
#include "compiler/Location.h"
#include "compiler/Subprogram.h"
#include "parser/AliasDef.h"
#include "parser/FunctionHeader.h"

namespace LL2W {
	struct ArrayValue;
	class  ASTNode;
	struct StructValue;
	struct Value;

	class Program {
		private:
			int highestIndex = -1;
			std::mutex mutex;

			std::string outputStruct(const StructValue &);
			std::string valuePrefix(size_t bitwidth);
			std::string outputValue(const TypePtr &type, const ValuePtr &value);
			std::string outputArray(const ArrayValue &);

		public:
			std::unordered_map<std::string, Function *> functions;
			std::string sourceFilename;
			std::unordered_map<std::string, FunctionHeader *> declarations;
			std::map<std::string, GlobalVarDef *> globals; // keys include the '@'
			/** A set of all globals to which references were emitted while outputting the data section. Doesn't include
			 *  the '@'. */
			std::set<std::string> referencedGlobals;
			std::map<int, std::unordered_set<FnAttr>> fnattrs;
			std::map<int, std::unordered_set<ParAttr>> parattrs;
			std::unordered_map<const std::string *, AliasDef *> aliases;
			std::map<int, File> files;
			std::map<int, Location> locations;
			std::map<int, Subprogram> subprograms;
			std::map<int, LexicalBlock> lexicalBlocks;
			/** A set of all LLVM debug indices found in the program. */
			std::set<int> debugIndices;
			/** A set of names of functions that do nothing except return their only argument. */
			std::set<std::string> simpleFunctions;
			/** A set of names of functions that do nothing but return void. */
			std::set<std::string> uselessFunctions;
			/** A map of names of functions that do nothing but return a constant to the constant they return. */
			std::map<std::string, std::shared_ptr<Value>> constantReturningFunctions;

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
