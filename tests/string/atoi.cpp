#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/string.hpp>

TEST(string, atoi) {
  EXPECT_EQ(42, ztl::atoi("42"));
  EXPECT_EQ(421, ztl::atoi("421"));
  EXPECT_EQ(-42, ztl::atoi(" -42"));
  EXPECT_EQ(-412, ztl::atoi("-412"));
  EXPECT_EQ(0, ztl::atoi("0"));
}
