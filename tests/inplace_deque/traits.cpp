#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_deque.hpp>

TEST(inplace_deque, traits) {
  using inplace_deque = ztl::inplace_deque<int, 1uz>;
  using iterator = inplace_deque::iterator;
  using const_iterator = inplace_deque::const_iterator;
  static_assert(std::ranges::random_access_range<inplace_deque>);
  static_assert(std::random_access_iterator<iterator>);
  static_assert(std::is_copy_constructible_v<iterator>);
  static_assert(std::is_copy_constructible_v<const_iterator>);
  static_assert(std::is_trivially_copy_constructible_v<iterator>);
  static_assert(std::is_trivially_copy_constructible_v<const_iterator>);
}