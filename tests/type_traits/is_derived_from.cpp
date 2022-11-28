#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a type is derived from some base
TEST(type_traits, is_derived_from) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::is_derived_from<H, C>::value));
  EXPECT_FALSE((ztl::is_derived_from_v<H, G>));
  EXPECT_TRUE((ztl::is_derived_from_v<F, B>));
  EXPECT_TRUE((ztl::is_derived_from<G, C>::value));
  EXPECT_TRUE((ztl::is_derived_from<G, E>::value));
  EXPECT_FALSE((ztl::is_derived_from_v<G, A>));
}
