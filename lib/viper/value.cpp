#include "value.h"

namespace viper {
value::value() : _node(nullptr), _value(std::nullopt) {}

value::value(const char *s) : _node(nullptr), _value(s) {}

value::value(const char *s, std::size_t count) : _node(nullptr), _value(std::in_place, s, count) {}

value::value(node_t node) : _node(node), _value(std::nullopt) {}

value::value(std::nullopt_t null) : _node(nullptr), _value(null) {}

value::operator std::string_view() {
	if (!_value) {
		if (_node == nullptr || !_node.is_keyval()) {
			return std::string_view{};
		}

		// optional value not set, update from node
		auto v = _node.val();
		_value = {v.data(), v.size()};
	}

	return _value.value();
}

std::optional<std::string_view> value::data() const noexcept {
	if (!_value && _node != nullptr && _node.is_keyval()) {
		auto v = _node.val();
		_value = {v.data(), v.size()};
	}

	return _value;
}
} // namespace viper
