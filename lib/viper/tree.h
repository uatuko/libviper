#pragma once

#include <ryml.hpp>
#include <vector>

#include "leaf.h"

namespace viper {
class tree {
public:
	tree() = default;
	tree(const std::vector<char> &data) :
		_tree(ryml::parse_in_arena(ryml::to_csubstr(data.data()))) {}
	tree(ryml::Tree t) : _tree(t) {}

	/**
	 *  Retrieve a leaf for a given path.
	 */
	viper::leaf leaf(const char *path);

private:
	ryml::Tree _tree;
};
} // namespace viper
