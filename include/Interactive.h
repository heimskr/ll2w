#ifndef INTERACTIVE_H_
#define INTERACTIVE_H_

#include "compiler/StackLocation.h"

namespace LL2W {
	class Program;
	void interactive(Program &);
	void printStackLocation(const StackLocation &);
}

#endif
