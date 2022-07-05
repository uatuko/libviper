#pragma once

#include <ryml.hpp>

#include "value.h"

namespace viper {
class leaf {
public:
	leaf() = delete;
	leaf(ryml::NodeRef n) : _node(n) {}

	constexpr explicit operator bool() const noexcept { return (_node != nullptr); }

	/**
	 * Retrieve the leaf value.
	 */
	viper::value value() const;

private:
	ryml::NodeRef _node;
};
} // namespace viper
