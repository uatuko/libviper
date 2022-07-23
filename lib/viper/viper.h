#pragma once

#include <memory>

#include "config.h"

namespace viper {
std::shared_ptr<config> conf();

void init(const char *name);
void init(const char *name, const char *path);
void init(const char *name, const std::filesystem::path &path);
} // namespace viper
