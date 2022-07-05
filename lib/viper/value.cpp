#include "value.h"

namespace viper {
value::operator std::string_view() {
	if (!has_value()) {
		if (_node == nullptr || !_node.is_keyval()) {
			return std::string_view{};
		}

		// optional value not set, update from node
		auto v = _node.val();
		emplace(std::string_view(v.data(), v.size()));
	}

	return std::optional<std::string_view>::value();
}
} // namespace viper
