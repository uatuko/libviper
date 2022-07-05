#include <gtest/gtest.h>

#include "leaf.h"

using namespace std::literals;

TEST(viper, leaf_value) {
	auto tree = ryml::parse_in_arena(R"(
key: value
map:
  key: value:map.key
array:
  - one
  - two
)");

	// Retrieve values for key-value types
	{
		auto leaf = viper::leaf(tree["key"]);
		EXPECT_TRUE(leaf);
		EXPECT_EQ("value"sv, *leaf.value());
	}

	// Retrieve values for map types
	{
		auto leaf = viper::leaf(tree["map"]);
		EXPECT_TRUE(leaf);
		EXPECT_FALSE(leaf.value());
	}

	// Retrieve values for array types
	{
		auto leaf = viper::leaf(tree["array"]);
		EXPECT_TRUE(leaf);
		EXPECT_FALSE(leaf.value());
	}
}
