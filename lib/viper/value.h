#pragma once

#include <optional>
#include <string_view>

#include <ryml.hpp>

namespace viper {
class value : public std::optional<std::string_view> {
public:
	/// Represents a value node
	typedef ryml::NodeRef node_t;

	value();
	value(const char *s);
	value(const char *s, std::size_t count);
	value(node_t node);
	value(std::nullopt_t null);

	constexpr operator bool() const noexcept { return has_value() || (_node != nullptr); }

	operator std::string_view();

private:
	node_t _node;
};
} // namespace viper
