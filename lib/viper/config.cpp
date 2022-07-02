#include "config.h"

namespace viper {
config::config(const char *name, const char *path) : _name(name), _path(path) {}

std::filesystem::path config::filename() {
	if (!_filename.empty()) {
		return _filename;
	}

	auto fpath = std::filesystem::path(_path) / "";
	for (const auto &ext : extensions) {
		auto fname = std::filesystem::path(_name);
		fname += ext;

		fpath.replace_filename(fname);
		auto status = std::filesystem::status(fpath);
		if (std::filesystem::is_regular_file(status)) {
			_filename = std::move(fpath);
			break;
		}
	}

	return _filename;
}
} // namespace viper
