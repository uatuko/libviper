#include <gtest/gtest.h>

#include "value.h"

using namespace std::literals;

TEST(viper, value_constructor) {
	{
		viper::value v = std::nullopt;
		EXPECT_FALSE(v.data());
	}
}

TEST(viper, value_conversions) {
	const char data[] = "0....5...9";

	// Full length
	{
		std::string_view v = viper::value(data);
		EXPECT_EQ("0....5...9"sv, v);
	}

	// Partials
	{
		std::string_view v = viper::value(data, 6);
		EXPECT_EQ("0....5"sv, v);

		v = viper::value(data + 5, 5);
		EXPECT_EQ("5...9"sv, v);
	}

	// Nulls
	{
		std::string_view v = viper::value{};
		EXPECT_EQ(0, v.size());
		EXPECT_EQ(""sv, v);
	}

	// From ryml::NodeRef
	{
		auto             t = ryml::parse_in_arena(R"(key: value)");
		std::string_view v = viper::value(t["key"]);
		EXPECT_EQ("value"sv, v);
	}

	// From null ryml::NodeRef
	{
		std::string_view v = viper::value(ryml::NodeRef{});
		EXPECT_EQ(0, v.size());
		EXPECT_EQ(""sv, v);
	}
}
