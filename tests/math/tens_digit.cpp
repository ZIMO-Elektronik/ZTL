#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/math.hpp>

TEST(math, tens_digit) {
  EXPECT_EQ(ztl::tens_digit(225), 2);
  EXPECT_EQ(ztl::tens_digit(4238261u), 6u);
  EXPECT_EQ(ztl::tens_digit(12813968329378591287ull), 8u);
}
