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

TEST(viper, config_node) {
	auto c = viper::config(ryml::parse_in_arena(R"(
key: value
object:
  key: value:object.key
  array:
    - one
    - two

nested:
  empty:
  object:
    key: value:nested.object
)"));

	// Lookup non-existent children
	{
		EXPECT_TRUE(c.node("non-existent") == nullptr);
		EXPECT_TRUE(c.node("object.non-existent") == nullptr);
		EXPECT_TRUE(c.node("nested.object.non-existent") == nullptr);
	}

	// Lookup invalid children
	{
		EXPECT_TRUE(c.node("object.array.invalid") == nullptr);
		EXPECT_TRUE(c.node("nested.empty.invalid") == nullptr);
	}

	// Lookup direct children
	{ EXPECT_TRUE(c.node("key") != nullptr); }

	// Lookup grand children
	{ EXPECT_TRUE(c.node("object.key") != nullptr); }

	// Lookup great grand children
	{ EXPECT_TRUE(c.node("nested.object.key") != nullptr); }

	// Lookup empty children
	{ EXPECT_TRUE(c.node("nested.empty") != nullptr); }

	// Lookup from a tree that isn't a map
	{
		auto c = viper::config(ryml::parse_in_arena(R"(
- one
- two
)"));

		EXPECT_TRUE(c.node("0") == nullptr);
		EXPECT_TRUE(c.node("one") == nullptr);
	}
}

TEST(viper, config_read) {
	// Successful read
	{
		auto c = viper::config("conf", VIPER_TESTDATA_PATH);
		EXPECT_NO_THROW(c.read());
	}
}
