#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string_view>
#include <ztl/string.hpp>

TEST(string, strcpy) {
  constexpr auto src{"copy this string pls"};
  std::array<char, ztl::strlen(src) + 1uz> dest{};
  ztl::strcpy(begin(dest), src);
  EXPECT_EQ(std::string_view{src}, std::string_view{cbegin(dest)});
}
