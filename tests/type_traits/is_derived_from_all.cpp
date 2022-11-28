#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a type is derived from all other types
TEST(type_traits, is_derived_from_all) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::is_derived_from_all_v<H, C, D, E>));
  EXPECT_FALSE((ztl::is_derived_from_all_v<H, C, D, E, G>));
  EXPECT_TRUE((ztl::is_derived_from_all_v<F, B>));
  EXPECT_TRUE((ztl::is_derived_from_all_v<G, C>));
  EXPECT_TRUE((ztl::is_derived_from_all_v<G, C, E>));
  EXPECT_FALSE((ztl::is_derived_from_all_v<G, C, E, H>));
}
