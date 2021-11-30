#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include "compiler/ExtractionResult.h"
#include "instruction/InstructionMeta.h"
#include "util/Makeable.h"

namespace LL2W {
	class ASTNode;
	class BasicBlock;
	class Variable;

	class Instruction {
		protected:
			bool extracted = false;
			Instruction(int index_): index(index_) {}

		public:
			std::weak_ptr<BasicBlock> parent;

			std::unordered_set<std::shared_ptr<Variable>> read, written;

			/** The order of the instruction within the entire function in its linearized representation. */
			int index;

			int debugIndex = -1;

			std::unordered_set<InstructionMeta> meta;

			virtual ~Instruction();

			virtual bool isTerminal() const = 0;

			/** Examines the instruction node to determine which virtual registers are read/written. Returns a pair of
			 *  the number of registers read and the number of registers written. */
			virtual ExtractionResult extract(bool force = false) = 0;

			/** Returns whether this instruction comes before another instruction. */
			bool operator<(const Instruction &) const;
			/** Returns whether this instruction comes after another instruction. */
			bool operator>(const Instruction &) const;

			virtual std::string debugExtra() { return ""; }
			virtual std::string toString() const;

			/** Attempts to replace a variable read by the instruction with another variable. Should be overridden by
			 *  any instruction that reads from a variable. */
			virtual bool replaceRead(std::shared_ptr<Variable>, std::shared_ptr<Variable>) {
				return false;
			}

			virtual bool canReplaceRead(std::shared_ptr<Variable>) const {
				return false;
			}

			/** Attempts to replace a variable written by the instruction with another variable. Should be overridden by
			 *  any instruction that writes to a variable. */
			virtual bool replaceWritten(std::shared_ptr<Variable>, std::shared_ptr<Variable>) {
				return false;
			}

			virtual bool canReplaceWritten(std::shared_ptr<Variable>) const {
				return false;
			}

			virtual bool maySpill() const { return true; }

			virtual bool isPhi() const { return false; }

			/** Whether it's valid for this instruction to have a debug intbang inserted after it. */
			virtual bool showDebug() const { return true; }

			virtual std::shared_ptr<Variable> doesRead(std::shared_ptr<Variable>) const;
			virtual std::shared_ptr<Variable> doesWrite(std::shared_ptr<Variable>) const;

			Instruction * setDebug(int debug_index, bool do_extract = false) {
				debugIndex = debug_index;
				if (do_extract)
					extract();
				return this;
			}

			Instruction * setDebug(const Instruction &other, bool do_extract = false) {
				debugIndex = other.debugIndex;
				if (do_extract)
					extract();
				return this;
			}

			Instruction * setDebug(const Instruction *other, bool do_extract = false) {
				debugIndex = other->debugIndex;
				if (do_extract)
					extract();
				return this;
			}

			Instruction * setDebug(const ASTNode &);
			Instruction * setDebug(const ASTNode *);
	};

	using InstructionPtr = std::shared_ptr<Instruction>;
}
