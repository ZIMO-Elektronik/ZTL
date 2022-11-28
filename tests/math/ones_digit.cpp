#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/math.hpp>

TEST(math, ones_digit) {
  EXPECT_EQ(ztl::ones_digit(225), 5);
  EXPECT_EQ(ztl::ones_digit(4238261u), 1u);
  EXPECT_EQ(ztl::ones_digit(static_cast<uint64_t>(12813968329378591287u)), 7u);
}
