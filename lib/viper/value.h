#pragma once

#include <optional>

#include <string_view>

namespace viper {
class value : public std::optional<std::string_view> {
public:
	using std::optional<std::string_view>::optional;

	operator std::string_view() const;
};
} // namespace viper
