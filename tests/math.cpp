#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/math.hpp>

TEST(math, align) {
  EXPECT_EQ(0u, ztl::align(4u, 0u));
  EXPECT_EQ(4u, ztl::align(4u, 3u));
  EXPECT_EQ(4u, ztl::align(4u, 4u));
  EXPECT_EQ(8u, ztl::align(4u, 5u));
  EXPECT_EQ(32u, ztl::align(32u, 10u));
  EXPECT_EQ(64u, ztl::align(32u, 33u));
  EXPECT_EQ(64u, ztl::align(32u, 64u));
}

TEST(math, digit) {
  EXPECT_EQ(ztl::tens_digit(225), 2);
  EXPECT_EQ(ztl::tens_digit(4238261u), 6u);
  EXPECT_EQ(ztl::tens_digit(12813968329378591287ull), 8u);
}

TEST(math, hundreds_digit) {
  EXPECT_EQ(ztl::hundreds_digit(225), 2);
  EXPECT_EQ(ztl::hundreds_digit(4238261u), 2u);
  EXPECT_EQ(ztl::hundreds_digit(12813968329378591287ull), 2u);
}

TEST(math, lerp) {
  constexpr auto y{ztl::lerp(45.0, 35.0, 64.0, 4.3313, 4.3944)};
  constexpr auto error{0.0001};
  EXPECT_NEAR(y, 4.3530, error);
}

TEST(math, lerp_x1_x2_equal) {
  constexpr auto y{ztl::lerp(42, 128, 128, 100, 200)};
  EXPECT_EQ(y, 100);
}

TEST(math, make_linspace) {
  constexpr auto error{0.001};

  {
    constexpr auto values{ztl::make_linspace<7u>(13.7, 19.83)};
    constexpr std::array expected{
      13.700, 14.722, 15.743, 16.765, 17.787, 18.808, 19.830};
    for (auto i{0u}; i < size(values); ++i)
      EXPECT_NEAR(values[i], expected[i], error);
  }

  {
    constexpr auto values{ztl::make_linspace<3u>(13, 100)};
    constexpr std::array expected{13, 56, 100};
    for (auto i{0u}; i < size(values); ++i)
      EXPECT_NEAR(values[i], expected[i], error);
  }
}

TEST(math, ones_digit) {
  EXPECT_EQ(ztl::ones_digit(225), 5);
  EXPECT_EQ(ztl::ones_digit(4238261u), 1u);
  EXPECT_EQ(ztl::ones_digit(12813968329378591287ull), 7u);
}

TEST(math, tens_digit) {
  EXPECT_EQ(ztl::tens_digit(225), 2);
  EXPECT_EQ(ztl::tens_digit(4238261u), 6u);
  EXPECT_EQ(ztl::tens_digit(12813968329378591287ull), 8u);
}
