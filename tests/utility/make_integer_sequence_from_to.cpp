#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/utility.hpp>

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