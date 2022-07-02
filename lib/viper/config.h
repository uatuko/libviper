#pragma once

namespace viper {
class config {
public:
	/**
	 * Set the name of config file
	 */
	void name(const char *n);

	/**
	 * Set the path to search for config file
	 */
	void path(const char *path);

	/**
	 * Read in configs
	 */
	void read();
};
} // namespace viper
