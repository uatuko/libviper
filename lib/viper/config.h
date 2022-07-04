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

	/**
	 * Return the config file used.
	 */
	std::filesystem::path filename();

	/**
	 * Retrieve a config value.
	 */
	template <typename T> inline std::optional<T> get(const char *key) {
		return leaf(key).value<T>();
	}

	/**
	 * Retrieve a config leaf for a given path.
	 */
	inline viper::leaf leaf(const char *path) { return _tree.leaf(path); }

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
