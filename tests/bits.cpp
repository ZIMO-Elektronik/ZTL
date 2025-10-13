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
  EXPECT_EQ((ztl::mask<39ull, 30ull, 12ull, 7ull, 1ull>),
            1ull << 39u | 1ull << 30u | 1ull << 12u | 1ull << 7u | 1ull << 1u);
  EXPECT_TRUE(
    (std::same_as<decltype(ztl::mask<30u, 12u, 7u, 1u>), uint32_t const>));
  EXPECT_TRUE(
    (std::same_as<decltype(ztl::mask<39ull, 30ull, 12ull, 7ull, 1ull>),
                  uint64_t const>));
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
  auto value{0b0101u};
  EXPECT_EQ(ztl::map_value_to<0b1101u>(value), 0b1001u);
}

TEST(bits, map_to_mask_contiguous) {
  auto value{0b0101u};
  EXPECT_EQ(ztl::map_value_to<0b1100u>(value), 0b100u);
}

TEST(bits, map_from_mask) {
  auto field{0b1001u};
  EXPECT_EQ(ztl::map_value_from<0b1101u>(field), 0b0101u);
}

TEST(bits, map_from_mask_contiguous) {
  auto field{0b1011u};
  EXPECT_EQ(ztl::map_value_from<0b1100u>(field), 0b10u);
}

TEST(bits, map_to_then_from_mask) {
  auto value{0b0101u};
  EXPECT_EQ(ztl::map_value_from<0b1101u>(ztl::map_value_to<0b1101u>(value)),
            value);
}

TEST(bits, map_to_with_template_mask) {
  auto value{0b0101u};
  EXPECT_EQ((ztl::map_value_to<ztl::mask<3u, 2u, 0u>>(value)), 0b1001u);
}

TEST(bits, runs_count) {
  EXPECT_EQ(ztl::runs_count(0b0u), 0uz);
  EXPECT_EQ(ztl::runs_count(0b1u), 1uz);
  EXPECT_EQ(ztl::runs_count(0b111u), 1uz);
  EXPECT_EQ(ztl::runs_count(0b101u), 2uz);
  EXPECT_EQ(ztl::runs_count(0b1011u), 2uz);
  EXPECT_EQ(ztl::runs_count(0b101001u), 3uz);
  EXPECT_EQ(ztl::runs_count(0b001011001111u), 3uz);
}
