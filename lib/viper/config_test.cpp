#include <gtest/gtest.h>

#include "config.h"

TEST(viper, config_filename) {
	// Default .yaml configs
	{
		auto c        = viper::config("conf", VIPER_TESTDATA_PATH);
		auto expected = std::filesystem::path(VIPER_TESTDATA_PATH) / "conf.yaml";

		EXPECT_EQ(expected, c.filename());
	}

	// Symlink to .yaml configs
	{
		auto c        = viper::config("symlink.conf", VIPER_TESTDATA_PATH);
		auto expected = std::filesystem::path(VIPER_TESTDATA_PATH) / "symlink.conf.yaml";

		EXPECT_EQ(expected, c.filename());
	}

	// Lookup configs with .yml extension
	{
		auto c        = viper::config("yml-config", VIPER_TESTDATA_PATH);
		auto expected = std::filesystem::path(VIPER_TESTDATA_PATH) / "yml-config.yml";

		EXPECT_EQ(expected, c.filename());
	}

	// Non-existent configs
	{
		auto c = viper::config("non-existent", VIPER_TESTDATA_PATH);
		EXPECT_TRUE(c.filename().empty());
	}
}

TEST(viper, config_read) {
	// Successful read
	{
		auto c = viper::config("conf", VIPER_TESTDATA_PATH);
		EXPECT_NO_THROW(c.read());
	}
}
