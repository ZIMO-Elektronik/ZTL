#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/fixed_string.hpp>
#include <ztl/string.hpp>

TEST(string, fixed_string) {
  constexpr ztl::fixed_string str{"hello world"};
  EXPECT_EQ(ztl::strlen(str.c_str()), 11uz);
}
