#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_deque.hpp>

TEST(inplace_deque, sort) {
  {
    ztl::inplace_deque values{2, 10, 4, 5, 1, 7, 8, 9, 3, 6};
    std::ranges::sort(values);
    constexpr ztl::inplace_deque expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(values, expected);
  }

  {
    ztl::inplace_deque<int, 10uz> values;
    values.push_back(2);
    values.push_back(10);
    values.push_back(4);
    values.push_back(5);
    values.push_back(1);
    values.push_front(7);
    values.push_front(6);
    values.push_front(3);
    values.push_front(9);
    values.push_front(8);
    std::ranges::sort(values);
    constexpr ztl::inplace_deque expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(values, expected);
  }
}
