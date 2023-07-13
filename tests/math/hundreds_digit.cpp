#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/math.hpp>

TEST(math, hundreds_digit) {
  EXPECT_EQ(ztl::hundreds_digit(225), 2);
  EXPECT_EQ(ztl::hundreds_digit(4238261u), 2u);
  EXPECT_EQ(ztl::hundreds_digit(12813968329378591287ull), 2u);
}
