#include <array>

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
	// bool
	{
		// boolean conversion is based on if an underlying value it set or not.
		EXPECT_FALSE(viper::value{});
		EXPECT_TRUE(viper::value("false"));

		auto t = ryml::parse_in_arena(R"(key: 0)");
		EXPECT_TRUE(viper::value(t["key"]));
		EXPECT_FALSE(viper::value(t["🤷"]));
	}

	// double
	{
		EXPECT_EQ(.0, double{viper::value{}});
		EXPECT_EQ(12.345, double{viper::value("12.345")});
		EXPECT_EQ(-1.23e-08, double{viper::value("-0.0000000123")});
		EXPECT_EQ(1.23e-04, double{viper::value("1.23e-4")});
	}

	// float
	{
		EXPECT_EQ(.0f, float{viper::value{}});
		EXPECT_EQ(1.23f, float{viper::value("1.23")});
		EXPECT_EQ(0.123f, float{viper::value("1.23e-1")});
	}

	// long
	{
		EXPECT_EQ(0, long{viper::value{}});
		EXPECT_EQ(0, long{viper::value("0b")});
		EXPECT_EQ(0, long{viper::value("0xzz")});
		EXPECT_EQ(0, long{viper::value("abcd")});

		EXPECT_EQ(12584, long{viper::value("12584")});
		EXPECT_EQ(123, long{viper::value("123,456,789.10")});
		EXPECT_EQ(123, long{viper::value("123_456_789")});
		EXPECT_EQ(22, long{viper::value("22.56")});
		EXPECT_EQ(125, long{viper::value("0x7d")});
		EXPECT_EQ(125, long{viper::value("0X7D")});
		EXPECT_EQ(15, long{viper::value("0xfg")}); // partial conversion from 0xf
		EXPECT_EQ(125, long{viper::value("0175")});
	}

	// std::string
	{
		EXPECT_EQ(""s, std::string{viper::value{}});
		EXPECT_EQ("string"s, std::string{viper::value("string")});
	}

	// std::string_view
	{
		// From ryml::NodeRef
		{
			auto t = ryml::parse_in_arena(R"(key: value)");
			EXPECT_EQ("value"sv, std::string_view{viper::value(t["key"])});
		}

		// From null ryml::NodeRef
		{
			auto v = std::string_view{viper::value(ryml::NodeRef{})};
			EXPECT_EQ(0, v.size());
			EXPECT_EQ(""sv, v);
		}

		// From const char*
		const char data[] = "0....5...9";

		// Full length
		{ EXPECT_EQ("0....5...9"sv, std::string_view{viper::value(data)}); }

		// Partials
		{
			EXPECT_EQ("0....5"sv, std::string_view{viper::value(data, 6)});
			EXPECT_EQ("5...9"sv, std::string_view{viper::value(data + 5, 5)});
		}

		// Nulls
		{
			auto v = std::string_view{viper::value{}};
			EXPECT_EQ(0, v.size());
			EXPECT_EQ(""sv, v);
		}
	}
}

TEST(viper, value_comparisons) {
	auto t = ryml::parse_in_arena(R"(
key: value
array:
  - one
  - two
)");

	// ==()
	{
		EXPECT_EQ(viper::value("value"), viper::value(t["key"]));
		EXPECT_EQ(viper::value(t["key"]), viper::value("value"));

		EXPECT_EQ(viper::value(t["array"]), viper::value(t["array"]));
	}
}

TEST(viper, value_get) {
	// value::get<T>() is used in the conversion operator and covered by conversion tests. Only the
	// exceptions are tested here.

	// value::get<bool>()
	// operator bool() is used to check if value{} is set which is used in conversion tests.
	{
		EXPECT_TRUE(viper::value("on").get<bool>());
		EXPECT_TRUE(viper::value("true").get<bool>());
		EXPECT_TRUE(viper::value("y").get<bool>());
		EXPECT_TRUE(viper::value("yes").get<bool>());

		EXPECT_FALSE(viper::value("false").get<bool>());
		EXPECT_FALSE(viper::value("N").get<bool>());
		EXPECT_FALSE(viper::value("no").get<bool>());
		EXPECT_FALSE(viper::value("off").get<bool>());
		EXPECT_FALSE(viper::value("OFF").get<bool>());

		EXPECT_FALSE(viper::value("1").get<bool>());
		EXPECT_FALSE(viper::value("0").get<bool>());
		EXPECT_FALSE(viper::value("string").get<bool>());
		EXPECT_FALSE(viper::value{}.get<bool>());

		auto t = ryml::parse_in_arena(R"(
boolean: true

array:
  - one
  - two
)");
		EXPECT_TRUE(viper::value(t["boolean"]).get<bool>());
	}
}

TEST(viper, value_iterator) {
	auto t = ryml::parse_in_arena(R"(
object:
  key: value

array:
  - one
  - two
)");

	{
		std::array<viper::value, 2> expected = {"one", "two"};

		std::size_t idx = 0;
		for (const auto &v : viper::value(t["array"])) {
			EXPECT_EQ(expected[idx++], v);
		}
	}
}
