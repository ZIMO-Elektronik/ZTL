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
