#include <gtest/gtest.h>

TEST(AdditionTests, CorrectAddition) { EXPECT_EQ(2 + 2, 4); }
TEST(AdditionTests, IncorrectAddition) { EXPECT_NE(2 + 2, 5); }
