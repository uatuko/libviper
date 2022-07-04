#include "leaf.h"

namespace viper {
template <> std::optional<bool> leaf::value() {
	if (_node == nullptr || !_node.is_keyval()) {
		return std::nullopt;
	}

	return (_node.val() == "true");
}

template <> std::optional<std::string> leaf::value() {
	if (_node == nullptr || !_node.is_keyval()) {
		return std::nullopt;
	}

	return _node.val().data();
}
} // namespace viper
