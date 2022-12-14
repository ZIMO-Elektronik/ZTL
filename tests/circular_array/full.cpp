#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, full) {
  ztl::circular_array<int, 4uz> c;
  EXPECT_TRUE(c.empty());

  // Push till full
  c.push_back(0);
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  EXPECT_TRUE(c.full());

  // Removing one element
  c.pop_back();
  EXPECT_FALSE(c.full());

  // Adding one element
  c.push_back(4);
  EXPECT_EQ(c.back(), 4);
  EXPECT_TRUE(c.full());

  // Trying to add further elements silently fails
  c.push_back(42);
  EXPECT_EQ(c.back(), 4);
}
