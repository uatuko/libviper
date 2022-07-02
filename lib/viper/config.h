#pragma once

#include <array>
#include <filesystem>

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
	 * Read in configs.
	 */
	void read();

private:
	const char *_name;
	const char *_path;

	std::filesystem::path _filename;
};
} // namespace viper
