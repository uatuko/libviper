#include <gtest/gtest.h>

#include "viper.h"

TEST(viper, init) {
	// void init(const char *name)
	{
		EXPECT_THROW(viper::init("non-existent"), std::filesystem::filesystem_error);
		EXPECT_TRUE(viper::conf()->filename().empty());
	}

	// void init(const char *name, const char *path)
	{
		EXPECT_NO_THROW(viper::init("conf", VIPER_TESTDATA_PATH));

		auto expected = std::filesystem::path(VIPER_TESTDATA_PATH) / "conf.yaml";
		EXPECT_EQ(expected, viper::conf()->filename());
	}

	// void init(const char *name, const std::filesystem::path &path)
	{
		EXPECT_NO_THROW(viper::init("symlink.conf", std::filesystem::path(VIPER_TESTDATA_PATH)));

		auto expected = std::filesystem::path(VIPER_TESTDATA_PATH) / "symlink.conf.yaml";
		EXPECT_EQ(expected, viper::conf()->filename());
	}
}
