#include "config.h"

#include <fstream>
#include <vector>

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

viper::value config::get(const char *path) const {
	auto n = node(path);
	return viper::value(n);
}

config::node_t config::node(const char *path) const {
	node_t ref = _tree.rootref();
	if (!ref.is_map()) {
		return {nullptr};
	}

	for (auto part : ryml::to_csubstr(path).split('.', 0)) {
		if (!ref.is_map()) {
			// Can't access any children
			ref = node_t{nullptr};
			break;
		}

		ref = ref[part];
		if (ref == nullptr) {
			break;
		}
	}

	return ref;
}

void config::read() {
	auto ec    = std::error_code{};
	auto fname = filename();
	auto size  = std::filesystem::file_size(fname, ec);

	if (ec) {
		throw std::filesystem::filesystem_error("[viper] Failed to get config file size", ec);
	}

	auto buffer = std::vector<char>(size, 0);
	auto f      = std::ifstream(fname, std::ios::binary);
	f.read(buffer.data(), buffer.size());

	try {
		f.exceptions(f.badbit | f.failbit);
	} catch (const std::ios_base::failure &e) {
		throw std::filesystem::filesystem_error("[viper] Failed to read configs", e.code());
	}

	_tree = ryml::parse_in_arena(ryml::to_csubstr(buffer.data()));
}
} // namespace viper
