#include "Strings.h"
#include <gtest/gtest.h>

TEST(Basic, DefaultConstructor) {
	Strings s;
}

TEST(Basic, ArgcArgvConstructor) {
	const char *argv[] = { "this", "that" };
	Strings s{sizeof(argv) / sizeof(char*), argv};
	EXPECT_EQ(s.at(0), "this");
	ASSERT_EQ(s.at(1), "that");
}

TEST(Basic, CopyConstructor) {
	const char *argv[] = { "this", "that" };
	Strings s_src{sizeof(argv) / sizeof(char*), argv};
	Strings s_dst{s_src};
	EXPECT_EQ(s_dst.at(0), "this");
	EXPECT_EQ(s_dst.at(1), "that");
}

TEST(ErrorHandling, InvalidArgvConstructor) {
	ASSERT_ANY_THROW({ Strings s(1, nullptr); });
}

TEST(ErrorHandling, OutOfBoundsAt) {
	Strings s{};
	ASSERT_ANY_THROW(s.at(0));
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
