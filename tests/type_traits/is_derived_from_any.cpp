#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a type is derived from any other types
TEST(type_traits, is_derived_from_any) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::is_derived_from_any_v<H, C>));
  EXPECT_TRUE((ztl::is_derived_from_any_v<H, C, A>));
  EXPECT_FALSE((ztl::is_derived_from_any_v<A, B, C, D, E>));
}
