#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a type has all bases from some other types
TEST(type_traits, has_base_from_all) {
  struct B0 {};
  struct B1 {};
  struct D1 : B0 {};
  struct D2 : B0, B1 {};

  B0 b0;
  auto& rb0{b0};

  D1 d1;
  auto& rd1{d1};

  EXPECT_TRUE((ztl::has_base_from_all<D1, B0>::value));
  EXPECT_TRUE((ztl::has_base_from_all<D1, decltype(b0)>::value));
  EXPECT_TRUE((ztl::has_base_from_all<D1, decltype(rb0)>::value));
  EXPECT_TRUE((ztl::has_base_from_all_v<decltype(d1), B0>));
  EXPECT_TRUE((ztl::has_base_from_all_v<decltype(rd1), B0>));
  EXPECT_FALSE((ztl::has_base_from_all_v<D1, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_all<B0, B0>::value));
  EXPECT_FALSE((ztl::has_base_from_all<D1, B1>::value));
  EXPECT_TRUE((ztl::has_base_from_all_v<D2, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_all<D2, B0>::value));
}
