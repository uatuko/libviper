#include "value.h"

namespace viper {
value::operator std::string_view() const {
	if (!has_value()) {
		return std::string_view();
	}

	return std::optional<std::string_view>::value();
}
} // namespace viper
