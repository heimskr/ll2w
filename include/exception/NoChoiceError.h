#include <stdexcept>

namespace LL2W {
	struct NoChoiceError: std::runtime_error {
		using std::runtime_error::runtime_error;
	};
}
