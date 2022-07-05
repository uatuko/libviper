#pragma once

#include <optional>
#include <string_view>

#include <ryml.hpp>

namespace viper {
class value : public std::optional<std::string_view> {
public:
	/// Represents a value node
	typedef ryml::NodeRef node_t;

	value() : std::optional<std::string_view>(std::nullopt), _node(nullptr) {}
	value(const char *s) : std::optional<std::string_view>(s), _node(nullptr) {}
	value(const char *s, std::size_t count) :
		std::optional<std::string_view>(std::in_place, s, count), _node(nullptr) {}
	value(node_t node) : std::optional<std::string_view>(std::nullopt), _node(node) {}
	value(std::nullopt_t null) : std::optional<std::string_view>(null), _node(nullptr) {}

	operator std::string_view();

private:
	node_t _node;
};
} // namespace viper
