// #ifndef COMPILER_MULTIINTERVAL_H_
// #define COMPILER_MULTIINTERVAL_H_

// #include <memory>
// #include <ostream>

// namespace LL2W {
// 	class BasicBlock;
// 	class Variable;

// 	struct MultiInterval {
// 		std::shared_ptr<BasicBlock> firstDefinition, lastUse;
// 		std::shared_ptr<Variable> variable = nullptr;
// 		int reg = -1;

// 		MultiInterval(std::shared_ptr<Variable>);
// 		int startpoint() const;
// 		int endpoint() const;

// 		int setRegister(int);

// 		operator std::string() const;
// 	};

// 	std::ostream & operator<<(std::ostream &, const Interval &);
// }

// #endif
