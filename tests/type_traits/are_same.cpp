#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Variadic version of std::is_same
TEST(type_traits, are_same) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::are_same_v<A, A, A>));
  EXPECT_FALSE((ztl::are_same_v<A, B>));
}
