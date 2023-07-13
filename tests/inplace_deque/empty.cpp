#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_deque.hpp>

TEST(inplace_deque, empty) {
  ztl::inplace_deque<int, 3uz> c;
  EXPECT_TRUE(c.empty());
  EXPECT_TRUE(empty(c));

  c.push_back(5);
  EXPECT_FALSE(c.empty());
  EXPECT_FALSE(empty(c));

  c.pop_back();
  EXPECT_TRUE(c.empty());
  EXPECT_TRUE(empty(c));

  // Trying to remove further elements causes undefined behavior
  EXPECT_DEATH(c.pop_back(), "");
}
