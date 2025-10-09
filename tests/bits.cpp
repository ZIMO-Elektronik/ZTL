#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/bits.hpp>

TEST(bits, mask) {
  EXPECT_EQ(ztl::mask<0u>, 1u << 0u);
  EXPECT_EQ(ztl::mask<1u>, 1u << 1u);
  EXPECT_EQ((ztl::mask<7u, 3u>), 1u << 7u | 1u << 3u);
  EXPECT_EQ((ztl::mask<3u, 7u>), 1u << 7u | 1u << 3u);
  EXPECT_EQ((ztl::mask<30u, 12u, 7u, 1u>),
            1u << 30u | 1u << 12u | 1u << 7u | 1u << 1u);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
TEST(bits, deprecated_make_mask) {
  EXPECT_EQ(ztl::make_mask(0u), 1u << 0u);
  EXPECT_EQ(ztl::make_mask(1u), 1u << 1u);
  EXPECT_EQ(ztl::make_mask(7u, 3u), 1u << 7u | 1u << 3u);
  EXPECT_EQ(ztl::make_mask(3u, 7u), 1u << 7u | 1u << 3u);
  EXPECT_EQ(ztl::make_mask(30u, 12u, 7u, 1u),
            1u << 30u | 1u << 12u | 1u << 7u | 1u << 1u);
}
#pragma GCC diagnostic pop

TEST(bits, map_to_mask) {
  auto const value{0b0101u};

  EXPECT_EQ(ztl::map_value_to<0b1101u>(value), 0b1001u);
}

TEST(bits, map_to_mask_contiguous) {
  auto const value{0b0101u};

  EXPECT_EQ(ztl::map_value_to<0b1100u>(value), 0b100u);
}

TEST(bits, map_from_mask) {
  auto const field{0b1001u};

  EXPECT_EQ(ztl::map_value_from<0b1101>(field), 0b0101u);
}

TEST(bits, map_from_mask_contiguous) {
  auto const field{0b1011u};

  EXPECT_EQ(ztl::map_value_from<0b1100u>(field), 0b10u);
}

TEST(bits, map_to_then_from_mask) {
  auto const value{0b0101u};

  EXPECT_EQ(ztl::map_value_from<0b1101u>(ztl::map_value_to<0b1101u>(value)),
            value);
}

TEST(bits, map_to_with_template_mask) {
  auto const value{0b0101u};

  EXPECT_EQ((ztl::map_value_to<ztl::mask<3u, 2u, 0u>>(value)), 0b1001u);
}
