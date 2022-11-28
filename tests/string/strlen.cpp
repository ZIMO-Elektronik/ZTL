#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/string.hpp>

TEST(string, strlen) {
  EXPECT_EQ(ztl::strlen("hello world"), 11uz);
  EXPECT_EQ(ztl::strlen("hello\nworld\n"), 12uz);
}
