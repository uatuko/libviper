#include <gtest/gtest.h>

#include "tree.h"

TEST(viper, tree_leaf) {
	auto t = viper::tree(ryml::parse_in_arena(R"(
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
		EXPECT_FALSE(t.leaf("non-existent"));
		EXPECT_FALSE(t.leaf("object.non-existent"));
		EXPECT_FALSE(t.leaf("nested.object.non-existent"));
	}

	// Lookup invalid children
	{
		EXPECT_FALSE(t.leaf("object.array.invalid"));
		EXPECT_FALSE(t.leaf("nested.empty.invalid"));
	}

	// Lookup direct children
	{ EXPECT_TRUE(t.leaf("key")); }

	// Lookup grand children
	{ EXPECT_TRUE(t.leaf("object.key")); }

	// Lookup great grand children
	{ EXPECT_TRUE(t.leaf("nested.object.key")); }

	// Lookup empty children
	{ EXPECT_TRUE(t.leaf("nested.empty")); }

	// Lookup from a tree that isn't a map
	{
		auto t = viper::tree(ryml::parse_in_arena(R"(
- one
- two
)"));

		EXPECT_FALSE(t.leaf("0"));
		EXPECT_FALSE(t.leaf("one"));
	}
}
