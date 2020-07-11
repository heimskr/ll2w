#ifndef COMPILER_INSTRUCTION_H_
#define COMPILER_INSTRUCTION_H_

#include <memory>
#include <string>
#include <unordered_set>

#include "compiler/ExtractionResult.h"

namespace LL2W {
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

			virtual bool maySpill() const { return true; }

			virtual bool isPhi() const { return false; }
	};

	using InstructionPtr = std::shared_ptr<Instruction>;
}

#endif
