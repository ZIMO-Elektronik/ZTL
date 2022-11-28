#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if more types are an integer sequence
TEST(type_traits, count_type) {
  EXPECT_EQ(1u, (ztl::count_type_v<int, double, char, int>));
  EXPECT_EQ(0u, (ztl::count_type_v<float, double, char, int>));
  EXPECT_EQ(2u, (ztl::count_type_v<int, double, int, int>));
  EXPECT_EQ(3u, (ztl::count_type_v<int, int, int, int>));
  EXPECT_NE(4u, (ztl::count_type_v<int, int, int, int>));
}
