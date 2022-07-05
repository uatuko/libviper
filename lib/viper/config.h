#pragma once

#include <array>
#include <filesystem>
#include <optional>

#include <ryml.hpp>

#include "value.h"

namespace viper {
class config {
public:
	/// List of supported extensions
	const std::array<const char *, 2> extensions = {".yaml", ".yml"};

	/// Represent a config tree
	typedef ryml::Tree tree_t;

	/// Represents a config node
	typedef ryml::NodeRef node_t;

	config() = delete;
	config(const char *name, const char *path);
	config(tree_t t);

	inline viper::value operator[](const char *key) const { return get(key); }

	/**
	 * Return the config file used.
	 */
	std::filesystem::path filename();

	/**
	 * Retrieve a config value.
	 */
	viper::value get(const char *path) const;

	/**
	 * Retrieve a config node for a given path.
	 */
	node_t node(const char *path) const;

	/**
	 * Read in configs.
	 */
	void read();

private:
	const char *_name;
	const char *_path;

	std::filesystem::path _filename;

	tree_t _tree;
};
} // namespace viper
