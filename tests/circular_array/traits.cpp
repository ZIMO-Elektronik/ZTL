#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, traits) {
  using circular_array = ztl::circular_array<int, 1uz>;
  using iterator = circular_array::iterator;
  using const_iterator = circular_array::const_iterator;
  static_assert(std::ranges::random_access_range<circular_array>);
  static_assert(std::random_access_iterator<iterator>);
  static_assert(std::is_copy_constructible_v<iterator>);
  static_assert(std::is_copy_constructible_v<const_iterator>);
  static_assert(std::is_trivially_copy_constructible_v<iterator>);
  static_assert(std::is_trivially_copy_constructible_v<const_iterator>);
}