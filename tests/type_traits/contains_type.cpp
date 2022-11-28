#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if tuple contains a type
TEST(type_traits, contains_type) {
  auto t0{std::make_tuple(42, 42.42, "aha")};
  auto const t1{std::make_tuple("jup", 42)};
  auto& rt0{t0};

  struct S {};
  auto p0{std::make_pair(42, S{})};

  EXPECT_TRUE((ztl::contains_type<int, decltype(t0)>::value));
  EXPECT_TRUE((ztl::contains_type_v<int, decltype(t0)>));
  EXPECT_TRUE((ztl::contains_type_v<int, decltype(rt0)>));
  EXPECT_FALSE((ztl::contains_type<float, decltype(t1)>::value));
  EXPECT_FALSE((ztl::contains_type_v<float, decltype(t1)>));
  EXPECT_TRUE((ztl::contains_type_v<char const*, decltype(t1)>));
  EXPECT_TRUE((ztl::contains_type_v<S, decltype(p0)>));
}
