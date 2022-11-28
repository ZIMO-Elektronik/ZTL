#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/math.hpp>

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
