#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_deque.hpp>

TEST(inplace_deque, resize) {
  ztl::inplace_deque<int, 10uz> c;
  c.push_front(10);
  c.push_front(9);
  c.push_front(8);
  c.push_front(7);
  c.pop_front();
  c.push_back(0);
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  c.push_back(4);
  c.push_back(5);
  c.push_back(6);
  EXPECT_EQ(size(c), 10uz);
  c.resize(5uz);
  EXPECT_EQ(size(c), 5uz);
}