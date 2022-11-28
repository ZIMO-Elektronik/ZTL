#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a type is a template
TEST(type_traits, is_template) {
  std::tuple<int> t;
  std::vector<char> v;
  std::basic_string<char> s;
  auto l{[] {}};

  EXPECT_TRUE(ztl::is_template_v<decltype(t)>);
  EXPECT_TRUE(ztl::is_template_v<decltype(v)>);
  EXPECT_TRUE(ztl::is_template_v<decltype(s)>);
  EXPECT_FALSE(ztl::is_template_v<int>);
  EXPECT_FALSE(ztl::is_template_v<decltype(l)>);
}
