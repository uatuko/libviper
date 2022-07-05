#pragma once

#include <array>
#include <filesystem>
#include <optional>

#include "tree.h"

namespace viper {
class config {
public:
	/// List of supported extensions
	const std::array<const char *, 2> extensions = {".yaml", ".yml"};

	config() = delete;
	config(const char *name, const char *path);

	inline viper::value operator[](const char *key) const { return get(key); }

	/**
	 * Return the config file used.
	 */
	std::filesystem::path filename();

	/**
	 * Retrieve a config value.
	 */
	viper::value get(const char *key) const;

	/**
	 * Retrieve a config leaf for a given path.
	 */
	viper::leaf leaf(const char *path) const;

	/**
	 * Read in configs.
	 */
	void read();

private:
	const char *_name;
	const char *_path;

	std::filesystem::path _filename;

	tree _tree;
};
} // namespace viper
