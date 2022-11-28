#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

// Check if a template can have an empty argument list (e.g. std::tuple<>)
TEST(type_traits, can_have_empty_argument_list) {
  EXPECT_FALSE(ztl::can_have_empty_argument_list<std::vector>::value);
  EXPECT_TRUE(ztl::can_have_empty_argument_list_v<std::tuple>);
  EXPECT_TRUE(ztl::can_have_empty_argument_list_v<std::void_t>);
  EXPECT_FALSE(ztl::can_have_empty_argument_list<std::is_base_of>::value);
}
