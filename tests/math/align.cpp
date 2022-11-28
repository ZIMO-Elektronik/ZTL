#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/math.hpp>

TEST(math, align) {
  EXPECT_EQ(0u, ztl::align(4u, 0u));
  EXPECT_EQ(4u, ztl::align(4u, 3u));
  EXPECT_EQ(4u, ztl::align(4u, 4u));
  EXPECT_EQ(8u, ztl::align(4u, 5u));
  EXPECT_EQ(32u, ztl::align(32u, 10u));
  EXPECT_EQ(64u, ztl::align(32u, 33u));
  EXPECT_EQ(64u, ztl::align(32u, 64u));
}
