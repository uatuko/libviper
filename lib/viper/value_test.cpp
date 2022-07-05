#include <gtest/gtest.h>

#include "value.h"

using namespace std::literals;

TEST(viper, value_constructor) {
	// Constructor inheritence
	{
		viper::value v = std::nullopt;
		EXPECT_FALSE(v.has_value());
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
		std::string_view v = viper::value(std::in_place, data, 6);
		EXPECT_EQ("0....5"sv, v);

		v = viper::value(std::in_place, data + 5, 5);
		EXPECT_EQ("5...9"sv, v);
	}

	// Nulls
	{
		std::string_view v = viper::value();
		EXPECT_EQ(0, v.size());
		EXPECT_EQ(""sv, v);
	}
}
