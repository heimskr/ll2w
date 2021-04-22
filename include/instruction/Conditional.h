#pragma once

#include <string>

#include "parser/Enums.h"

namespace LL2W {
	struct Conditional {
		Condition condition;
		Conditional(Condition);
		std::string conditionPrefix() const;
	};
}
