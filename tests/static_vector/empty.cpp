#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/static_vector.hpp>

TEST(static_vector, empty) {
  ztl::static_vector<int, 3uz> c;
  EXPECT_TRUE(c.empty());

  c.push_back(5);
  EXPECT_FALSE(c.empty());

  c.pop_back();
  EXPECT_TRUE(c.empty());

  // Trying to remove further elements causes undefined behavior
  EXPECT_DEATH(c.pop_back(), "");
}
