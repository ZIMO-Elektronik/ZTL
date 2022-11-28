#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, empty) {
  ztl::circular_array<int, 3uz> c;
  EXPECT_TRUE(c.empty());

  c.push_back(5);
  EXPECT_FALSE(c.empty());

  c.pop_back();
  EXPECT_TRUE(c.empty());

  c.push_front(42);
  EXPECT_FALSE(c.empty());
}
