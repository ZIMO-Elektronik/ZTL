#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a type is a specialization of a template
TEST(type_traits, is_specialization_of) {
  auto t0{std::make_tuple(42)};
  auto const t1{std::make_tuple(42)};
  std::vector<int> volatile v0{42};

  EXPECT_TRUE((ztl::is_specialization_of_v<decltype(t0), std::tuple>));
  EXPECT_TRUE((ztl::is_specialization_of_v<decltype(t1), std::tuple>));
  EXPECT_TRUE(
    (ztl::is_specialization_of_v<decltype(t0), std::tuple, std::pair>));
  EXPECT_FALSE((ztl::is_specialization_of_v<decltype(t0), std::pair>));
  EXPECT_TRUE((ztl::is_specialization_of_v<decltype(v0), std::vector>));
}
