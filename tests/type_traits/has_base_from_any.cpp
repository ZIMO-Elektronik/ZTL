#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a type has any base from some other types (basically variadic
// version of is_base the other way round)
TEST(type_traits, has_base_from_any) {
  struct B0 {};
  struct B1 {};
  struct D1 : B0 {};
  struct D2 : B1 {};

  B0 b0;
  auto& rb0{b0};

  D2 d2;
  auto& rd2{d2};

  EXPECT_TRUE((ztl::has_base_from_any<D1, B0>::value));
  EXPECT_TRUE((ztl::has_base_from_any_v<D1, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_any_v<D1, decltype(rb0), B1>));
  EXPECT_TRUE((ztl::has_base_from_any<B0, B0>::value));
  EXPECT_FALSE((ztl::has_base_from_any<D1, B1>::value));
  EXPECT_TRUE((ztl::has_base_from_any_v<D2, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_any_v<decltype(d2), B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_any_v<decltype(rd2), B0, B1>));
  EXPECT_FALSE((ztl::has_base_from_any<D2, B0>::value));
}
