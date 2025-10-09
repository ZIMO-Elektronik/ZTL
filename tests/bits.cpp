#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/bits.hpp>

// Create bit mask
TEST(bits, make_mask) {
  EXPECT_EQ(ztl::make_mask(0u), 1u << 0u);
  EXPECT_EQ(ztl::make_mask(1u), 1u << 1u);
  EXPECT_EQ(ztl::make_mask(7u, 3u), 1u << 7u | 1u << 3u);
  EXPECT_EQ(ztl::make_mask(3u, 7u), 1u << 7u | 1u << 3u);
  EXPECT_EQ(ztl::make_mask(30u, 12u, 7u, 1u),
            1u << 30u | 1u << 12u | 1u << 7u | 1u << 1u);
}

TEST(bits, make_value) {
  auto const value{0b0101u};
  auto const mask{0b1101u};

  EXPECT_EQ(ztl::make_value<false>(mask, value), 0b1001u);
}

TEST(bits, make_value_packed_mask) {
  auto const value{0b0101u};
  auto const mask{0b1100u};

  EXPECT_EQ(ztl::make_value<false>(mask, value), 0b100u);
  EXPECT_EQ(ztl::make_value<true>(mask, value), 0b100u);
}

TEST(bits, extract_value) {
  auto const field{0b1001u};
  auto const mask{0b1101u};

  EXPECT_EQ(ztl::extract_value<false>(mask, field), 0b0101u);
}

TEST(bits, extract_value_packet_mask) {
  auto const field{0b1011u};
  auto const mask{0b1100u};

  EXPECT_EQ(ztl::extract_value<false>(mask, field), 0b10u);
  EXPECT_EQ(ztl::extract_value<true>(mask, field), 0b10u);
}

TEST(bits, make_value_then_extract_value) {
  auto const value{0b0101u};
  auto const mask{0b1101u};

  EXPECT_EQ(ztl::extract_value<false>(mask, ztl::make_value(mask, value)),
            value);
}
