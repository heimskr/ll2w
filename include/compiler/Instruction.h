#ifndef COMPILER_INSTRUCTION_H_
#define COMPILER_INSTRUCTION_H_

#include <string>
#include <vector>

namespace LL2W {
	class BasicBlock;

	class Instruction {
		protected:
			bool extracted = false;
			Instruction(int index_): index(index_) {}

		public:
			BasicBlock *parent = nullptr;
			std::vector<int> read, written;
			/** The order of the instruction within the entire function in its linearized representation. */
			int index;

			virtual ~Instruction();

			virtual bool isTerminal() const = 0;

			/** Examines the instruction node to determine which virtual registers are read/written. Returns a pair of
			 *  the number of registers read and the number of registers written. */
			virtual std::pair<char, char> extract(bool force = false) = 0;

			/** Returns whether this instruction comes before another instruction. */
			bool operator<(const Instruction &) const;
			/** Returns whether this instruction comes after another instruction. */
			bool operator>(const Instruction &) const;

			virtual std::string debugExtra() { return ""; }
	};
}

#endif
