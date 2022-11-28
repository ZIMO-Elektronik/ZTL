#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/utility.hpp>

// Convert index sequence to bitmask
TEST(utility, index_sequence2mask) {
  {
    constexpr auto m{ztl::index_sequence2mask(std::make_index_sequence<0uz>{})};
    EXPECT_EQ(m, 0b0u);
  }

  {
    constexpr auto m{ztl::index_sequence2mask(std::make_index_sequence<4uz>{})};
    EXPECT_EQ(m, 0b1111u);
  }

  {
    std::index_sequence<3uz, 5uz> r{};
    auto m{ztl::index_sequence2mask(r)};
    EXPECT_EQ(m, 0b101000);
  }

  {
    std::integer_sequence<size_t, 3uz, 5uz> r{};
    auto m{ztl::index_sequence2mask(r)};
    EXPECT_EQ(m, 0b101000);
  }
}
