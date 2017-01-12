#include "first.h"
#include "gtest/gtest.h"

TEST(Factorial, positives)
{
  ASSERT_EQ(1,recursive(1));
  ASSERT_EQ(120,recursive(5));
}

TEST(Factorial, negatives)
{
  ASSERT_EQ(1, recursive(-1));
  ASSERT_EQ(1, recursive(-5));
}

TEST(Factorial, zero)
{
  ASSERT_EQ(1, recursive(0));
}
