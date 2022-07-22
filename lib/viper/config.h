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
	config(const char *name, std::filesystem::path path = std::filesystem::current_path());
	config(tree_t t);

	inline viper::value operator[](const char *key) const { return get(key); }

	/**
	 * Retrieve a config value from environment variables.
	 */
	viper::value env(const char *path) const noexcept;

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

	/**
	 * Retrieve a config value from the config file.
	 */
	viper::value val(const char *path) const noexcept;

private:
	const char *_name;

	std::filesystem::path _path;
	std::filesystem::path _filename;

	tree_t _tree;
};
} // namespace viper
