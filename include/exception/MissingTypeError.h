#include <stdexcept>

namespace LL2W {
	struct MissingTypeError: std::runtime_error {
		using std::runtime_error::runtime_error;
	};
}
