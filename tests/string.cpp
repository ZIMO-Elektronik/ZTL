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

TEST(string, strcmp) {
  EXPECT_EQ(0, ztl::strcmp("hello", "hello"));
  EXPECT_EQ(0, ztl::strcmp("hello", "hel"));
  EXPECT_GT(0, ztl::strcmp("a", "b"));
  EXPECT_LT(0, ztl::strcmp("b", "a"));
}

TEST(string, strcpy) {
  constexpr auto src{"copy this string pls"};
  std::array<char, ztl::strlen(src) + 1uz> dest{};
  ztl::strcpy(begin(dest), src);
  EXPECT_EQ(std::string_view{src}, std::string_view{cbegin(dest)});
}

TEST(string, strlen) {
  EXPECT_EQ(ztl::strlen("hello world"), 11uz);
  EXPECT_EQ(ztl::strlen("hello\nworld\n"), 12uz);
}

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

TEST(string, strstr) {
  EXPECT_TRUE(ztl::strstr("Hello World", "World"));
  EXPECT_FALSE(ztl::strstr("Hello World", "Dreamland"));
}