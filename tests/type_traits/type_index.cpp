#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Get index of type in typelist
TEST(type_traits, type_index) {
  auto i0 = ztl::type_index<int, double, char, int>{};
  EXPECT_EQ(2u, i0);

  auto i1 = ztl::type_index<float&, double, char, int, float&, int>{};
  EXPECT_EQ(3u, i1);

  auto i2 = ztl::type_index<int, double, int, char>{};
  EXPECT_EQ(1u, i2);

  // fails with static_assertion
  //  auto i = ztl::type_index<int, double, char, float>{};
  //  EXPECT_EQ(0, i);
}
