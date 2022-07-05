#include "leaf.h"

namespace viper {
viper::value leaf::value() const {
	if (_node == nullptr || !_node.is_keyval()) {
		return std::nullopt;
	}

	auto v = _node.val();
	return viper::value(std::in_place, v.data(), v.size());
}
} // namespace viper
