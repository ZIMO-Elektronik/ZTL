#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/utility.hpp>

TEST(utility, get) {
  auto is{std::integer_sequence<int, 1, 2, 3>{}};
  static_assert((
    std::same_as<decltype(ztl::get<0uz>(is)), std::integral_constant<int, 1>>));
  static_assert((
    std::same_as<decltype(ztl::get<1uz>(is)), std::integral_constant<int, 2>>));
  static_assert((
    std::same_as<decltype(ztl::get<2uz>(is)), std::integral_constant<int, 3>>));
}

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

TEST(utility, make_integer_sequence_from_to) {
  {
    auto s{ztl::make_integer_sequence_from_to<int, 0, 5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, 0, 1, 2, 3, 4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<uint16_t, 2, 5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<uint16_t, 2, 3, 4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -5, 0>()};
    EXPECT_TRUE((std::same_as<decltype(s),
                              std::integer_sequence<int, -5, -4, -3, -2, -1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -5, 2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<int, -5, -4, -3, -2, -1, 0, 1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -0, -5>()};
    EXPECT_TRUE((std::same_as<decltype(s),
                              std::integer_sequence<int, -0, -1, -2, -3, -4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -2, -5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, -2, -3, -4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, 5, 0>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, 5, 4, 3, 2, 1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<size_t, 5, 2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<size_t, 5, 4, 3>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int8_t, -5, -0>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<int8_t, -5, -4, -3, -2, -1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -5, -2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, -5, -4, -3>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, 2, -5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<int, 2, 1, 0, -1, -2, -3, -4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<char, 5, -2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<char, 5, 4, 3, 2, 1, 0, -1>>));
  }
}