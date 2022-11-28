#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/math.hpp>

// Lerp
TEST(math, lerp) {
  constexpr auto y{ztl::lerp(45.0, 35.0, 64.0, 4.3313, 4.3944)};
  constexpr auto error{0.0001};
  EXPECT_NEAR(y, 4.3530, error);
}

TEST(math, lerp_x1_x2_equal) {
  constexpr auto y{ztl::lerp(42, 128, 128, 100, 200)};
  EXPECT_EQ(y, 100);
}