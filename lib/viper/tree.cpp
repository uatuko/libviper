#include "tree.h"

namespace viper {
viper::leaf tree::leaf(const char *path) {
	ryml::NodeRef ref = _tree.rootref();
	if (!ref.is_map()) {
		return viper::leaf(nullptr);
	}

	for (auto part : ryml::to_csubstr(path).split('.', 0)) {
		if (!ref.is_map()) {
			// Can't access any children
			ref = ryml::NodeRef(nullptr);
			break;
		}

		ref = ref[part];
		if (ref == nullptr) {
			break;
		}
	}

	return viper::leaf(ref);
}
} // namespace viper
