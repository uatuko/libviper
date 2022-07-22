#include <iostream>

#include <viper/viper.h>

int main() {
	// An instance of `viper::config` can be used to read config files and retrieve config values.
	{
		// Initialise
		auto conf = viper::config("app.conf", EXAMPLE_CONF_PATH);
		std::cout << "Attempting to read configs from file: " << conf.filename() << std::endl;

		// Read configs
		try {
			conf.read();
		} catch (const std::exception &e) {
			std::cout << "[FATAL] " << e.what() << std::endl;
			return EXIT_FAILURE;
		}

		// Retrieve config values
		std::cout << "[app.name] " << conf["app.name"].str() << std::endl;
	}

	// For convenience, libviper offers configs to be initialised and used as a shared single
	// instance.
	try {
		viper::init("app.conf", EXAMPLE_CONF_PATH);
	} catch (const std::exception &e) {
		std::cout << "[FATAL] " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	auto conf = *viper::conf(); // deference `std::shared_ptr<viper::config>`` to `viper::config`
	std::cout << "Using shared configs (file: " << conf.filename() << ")" << std::endl;

	// Using supscript operator to access config values
	{
		viper::value v = conf["app.name"]; // or auto v = conf.get("app.name");
		std::cout << "[app.name] " << v.str() << std::endl;
	}

	// Retrieve config values without considering potential overrides
	{
		viper::value v = conf.val("key");
		std::cout << "[key] " << v.str() << std::endl;
	}

	// Retrieve a config value from environment variables
	{
		viper::value v = conf.env("path.to-key"); // read from PATH_TO_KEY environment variable
		std::cout << "[path.to-key] " << v.str() << std::endl;
	}

	// Iterating through values
	{
		std::cout << "[array]" << std::endl;

		std::size_t idx = 0;
		for (const auto &v : conf["array"]) {
			std::cout << "  [" << idx++ << "] " << v.str() << std::endl;
		}
	}

	// Type conversions
	{
		std::cout << std::boolalpha;

		std::cout << "<std::string>[app.name] " << std::string(conf["app.name"]) << std::endl;
		std::cout << "<bool>[app.debug] " << bool{conf["app.debug"]} << std::endl;
		std::cout << "<bool>[object.boolean] " << bool{conf["object.boolean"]} << std::endl;
		std::cout << "<double>[object.double] " << double{conf["object.double"]} << std::endl;
		std::cout << "<float>[object.float] " << conf["object.float"].get<float>() << std::endl;
		std::cout << "<long>[object.number] " << long{conf["object.number"]} << std::endl;

		viper::value v = conf["object.number"];
		std::cout << "<long>[object.number] " << v.get<long>() << std::endl;
	}

	return EXIT_SUCCESS;
}
