#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Get index of type in tuple
TEST(type_traits, tuple_index) {
  using Tuple = std::tuple<int, double, char>;

  auto i0{ztl::tuple_index_v<int, Tuple>};
  EXPECT_EQ(i0, 0u);

  auto i1{ztl::tuple_index_v<double, Tuple>};
  EXPECT_EQ(i1, 1u);

  auto i2{ztl::tuple_index_v<char, Tuple>};
  EXPECT_EQ(i2, 2u);

  // fails with static_assertion
  // auto i3{ztl::tuple_index_v<std::string, Tuple>};
  // EXPECT_EQ(i3, 0u);
}
