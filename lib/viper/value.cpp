#include "value.h"

namespace viper {
value::value() : std::optional<std::string_view>(std::nullopt), _node(nullptr) {}

value::value(const char *s) : std::optional<std::string_view>(s), _node(nullptr) {}

value::value(const char *s, std::size_t count) :
	std::optional<std::string_view>(std::in_place, s, count), _node(nullptr) {}

value::value(node_t node) : std::optional<std::string_view>(std::nullopt), _node(node) {}

value::value(std::nullopt_t null) : std::optional<std::string_view>(null), _node(nullptr) {}

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
