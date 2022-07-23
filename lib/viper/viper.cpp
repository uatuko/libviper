#include "viper.h"

static std::shared_ptr<viper::config> _conf = nullptr;

namespace viper {
std::shared_ptr<config> conf() {
	return _conf;
}

void init(const char *name) {
	_conf = std::make_shared<config>(name);
	_conf->read();
}

void init(const char *name, const char *path) {
	_conf = std::make_shared<config>(name, path);
	_conf->read();
}

void init(const char *name, const std::filesystem::path &path) {
	_conf = std::make_shared<config>(name, path);
	_conf->read();
}
} // namespace viper
