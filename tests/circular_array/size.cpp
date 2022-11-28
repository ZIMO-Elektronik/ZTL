#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, size) {
  ztl::circular_array<int, 10uz> c;
  EXPECT_EQ(0uz, size(c));

  c.push_back(42);
  EXPECT_EQ(1uz, size(c));

  c.pop_back();
  EXPECT_EQ(0uz, size(c));

  c.push_front(43);
  EXPECT_EQ(1uz, size(c));
}