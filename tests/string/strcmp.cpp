#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/string.hpp>

TEST(string, strcmp) {
  EXPECT_EQ(0, ztl::strcmp("hello", "hello"));
  EXPECT_EQ(0, ztl::strcmp("hello", "hel"));
  EXPECT_GT(0, ztl::strcmp("a", "b"));
  EXPECT_LT(0, ztl::strcmp("b", "a"));
}