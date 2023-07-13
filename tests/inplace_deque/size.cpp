#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_deque.hpp>

TEST(inplace_deque, size) {
  ztl::inplace_deque<int, 10uz> c;
  EXPECT_EQ(0uz, size(c));

  c.push_back(42);
  EXPECT_EQ(1uz, size(c));

  c.pop_back();
  EXPECT_EQ(0uz, size(c));

  c.push_front(43);
  EXPECT_EQ(1uz, size(c));
}