#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/utility.hpp>

TEST(utility, get) {
  auto is{std::integer_sequence<int, 1, 2, 3>{}};
  static_assert((
    std::same_as<decltype(ztl::get<0uz>(is)), std::integral_constant<int, 1>>));
  static_assert((
    std::same_as<decltype(ztl::get<1uz>(is)), std::integral_constant<int, 2>>));
  static_assert((
    std::same_as<decltype(ztl::get<2uz>(is)), std::integral_constant<int, 3>>));
}
