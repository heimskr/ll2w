#pragma once

#include "compiler/StackLocation.h"

namespace LL2W {
	class Program;
	void interactive(Program &, Function * = nullptr);
	void printStackLocation(const StackLocation &);
}
