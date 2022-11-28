#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/string.hpp>

TEST(string, strncpy) {
  {
    constexpr auto src{"copy this string pls"};
    std::array<char, ztl::strlen(src) + 1uz> dest{};
    ztl::strncpy(begin(dest), src, size(dest));
    EXPECT_EQ(std::string_view{src}, std::string_view{cbegin(dest)});
  }

  {
    constexpr auto src{"copy this string pls"};
    std::array<char, ztl::strlen(src) + 1uz> dest{};
    ztl::strncpy(begin(dest), src, 5uz);
    EXPECT_EQ(std::string_view{"copy "}, std::string_view{cbegin(dest)});
  }

  {
    constexpr auto src{"copy this string pls"};
    std::array<char, 50uz> dest{};
    ztl::strncpy(begin(dest), src, size(dest));
    EXPECT_EQ(std::string_view{src}, std::string_view{cbegin(dest)});
  }
}
