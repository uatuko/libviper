#pragma once

#include <optional>
#include <string_view>

#include <ryml.hpp>

namespace viper {
class value {
public:
	/// Represents a value node
	typedef ryml::NodeRef node_t;

	value();
	value(const char *s);
	value(const char *s, std::size_t count);
	value(node_t node);
	value(std::nullopt_t null);

	constexpr explicit operator bool() const noexcept { return _value || (_node != nullptr); }

	template <typename T> explicit operator T() const noexcept { return get<T>(); }

	std::optional<std::string_view> data() const noexcept;

	/**
	 * Retrieve the stored value converted to a given type.
	 *
	 * Specialisations:
	 *   - template <> bool get() const noexcept;
	 *   - template <> long get() const noexcept;
	 *   - template <> std::string get() const noexcept;
	 *   - template <> std::string_view get() const noexcept;
	 */
	template <typename T> T get() const noexcept;

	std::string_view str() const noexcept;

private:
	node_t _node;

	mutable std::optional<std::string_view> _value;
};
} // namespace viper
