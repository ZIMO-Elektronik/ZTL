#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/string.hpp>

TEST(string, strstr) {
  EXPECT_TRUE(ztl::strstr("Hello World", "World"));
  EXPECT_FALSE(ztl::strstr("Hello World", "Dreamland"));
}