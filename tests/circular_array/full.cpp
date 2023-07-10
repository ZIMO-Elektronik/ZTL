#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, full) {
  ztl::circular_array<int, 4uz> c;
  EXPECT_TRUE(c.empty());
  EXPECT_TRUE(empty(c));

  // Push till full
  c.push_back(0);
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  EXPECT_TRUE(c.full());
  EXPECT_TRUE(full(c));

  // Removing one element
  c.pop_back();
  EXPECT_FALSE(c.full());
  EXPECT_FALSE(full(c));

  // Adding one element
  c.push_back(4);
  EXPECT_EQ(c.back(), 4);
  EXPECT_TRUE(c.full());
  EXPECT_TRUE(full(c));

  // Trying to add further elements causes undefined behavior
  EXPECT_DEATH(c.push_back(42), "");
}
