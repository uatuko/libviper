#pragma once

#include <optional>
#include <ryml.hpp>
#include <string>

namespace viper {
class leaf {
public:
	leaf() = delete;
	leaf(ryml::NodeRef n) : _node(n) {}

	constexpr explicit operator bool() const noexcept { return (_node != nullptr); }

	/**
	 * Retrieve a config value.
	 */
	template <typename T> std::optional<T> value() { return std::nullopt; }

	template <> std::optional<bool>        value();
	template <> std::optional<std::string> value();

private:
	ryml::NodeRef _node;
};
} // namespace viper
