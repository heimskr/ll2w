#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "compiler/ExtractionResult.h"
#include "compiler/LivePoint.h"
#include "instruction/InstructionMeta.h"
#include "util/Makeable.h"

namespace llvm {
	class Instruction;
}

namespace LL2W {
	class ASTNode;
	class BasicBlock;
	class Variable;

	using VariablePtr = std::shared_ptr<Variable>;

	class Instruction: public LivePoint {
		protected:
			bool extracted = false;
			Instruction(int index_): index(index_) {}

		public:
			std::weak_ptr<BasicBlock> parent;

			std::unordered_set<VariablePtr> read;
			std::unordered_set<VariablePtr> written;

			/** The order of the instruction within the entire function in its linearized representation. */
			int index;

			int debugIndex = -1;

			/** Whether to treat this instruction as not reading any variables. */
			bool secretReads = false;

			/** Whether to treat this instruction as not writing any variables. */
			bool secretWrites = false;

			std::unordered_set<InstructionMeta> meta;

			virtual ~Instruction() = default;

			virtual bool isTerminal() const = 0;

			/** Examines the instruction node to determine which virtual registers are read/written. Returns a pair of
			 *  the number of registers read and the number of registers written. */
			virtual ExtractionResult extract(bool force = false) = 0;

			/** Returns whether this instruction comes before another instruction. */
			bool operator<(const Instruction &) const;
			/** Returns whether this instruction comes after another instruction. */
			bool operator>(const Instruction &) const;

			virtual std::string debugExtra() const { return ""; }
			virtual std::string toString() const;

			/** Attempts to replace a variable read by the instruction with another variable. Should be overridden by
			 *  any instruction that reads from a variable. */
			virtual bool replaceRead(const VariablePtr &, const VariablePtr &) {
				return false;
			}

			virtual bool canReplaceRead(const VariablePtr &) const {
				return false;
			}

			/** Attempts to replace a variable written by the instruction with another variable. Should be overridden by
			 *  any instruction that writes to a variable. */
			virtual bool replaceWritten(const VariablePtr &, const VariablePtr &) {
				return false;
			}

			virtual bool canReplaceWritten(const VariablePtr &) const {
				return false;
			}

			/** Attempts to replace a label referenced by the instruction with another label. Should be overridden by
			 *  any instruction that references labels. */
			virtual bool replaceLabel(const std::string *to_replace, const std::string *replace_with) {
				(void) to_replace;
				(void) replace_with;
				return false;
			}

			virtual bool maySpill() const { return true; }

			virtual bool isPhi() const { return false; }

			/** Whether it's valid for this instruction to have a debug intbang inserted after it. */
			virtual bool showDebug() const { return true; }

			virtual VariablePtr doesRead(const VariablePtr &) const;
			virtual VariablePtr doesWrite(const VariablePtr &) const;

			Instruction * setDebug(int debug_index, bool do_extract = false) {
				debugIndex = debug_index;
				if (do_extract)
					extract();
				return this;
			}

			Instruction * setDebug(const Instruction &other, bool do_extract = false) {
				return setDebug(other.debugIndex, do_extract);
			}

			Instruction * setDebug(const Instruction *other, bool do_extract = false) {
				return setDebug(other->debugIndex, do_extract);
			}

			Instruction * setDebug(const ASTNode &);
			Instruction * setDebug(const ASTNode *);

			Instruction * setSecret(bool reads, bool writes) {
				secretReads = reads;
				secretWrites = writes;
				return this;
			}

			Instruction * setSecret() {
				return setSecret(true, true);
			}

			virtual std::vector<const std::string *> getLabels() const {
				return {};
			}

			/** Returns true if the instruction might (depending on run-time conditions) jump elsewhere or might just
			 *  continue to the next instruction. */
			virtual bool canFallThrough() const {
				return false;
			}

			virtual bool holdsLabels() const {
				return false;
			}

			/** Returns whether the instruction is of a type that ends a basic block. */
			virtual bool isBlockTerminal() const {
				return false;
			}

			virtual bool fixSignedness() {
				return false;
			}

			virtual Instruction * copy() const = 0;

			/** We care about equality only for regular Why instructions, unless our needs change in the future. */
			virtual bool operator==(const Instruction &) const {
				return false;
			}

			/** Returns true if the types of the instruction need to be fixed somehow. */
			virtual bool typeMismatch() const {
				return false;
			}

			std::unordered_set<VariablePtr> & getRead() final;
			std::unordered_set<VariablePtr> & getWritten() final;
			int getIndex() const final;
	};

	using InstructionPtr = std::shared_ptr<Instruction>;

	std::ostream & operator<<(std::ostream &, const Instruction &);
	std::ostream & operator<<(std::ostream &, const InstructionPtr &);
}
