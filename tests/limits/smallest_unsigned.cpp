#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/limits.hpp>

TEST(limits, smallest_unsigned) {
  EXPECT_TRUE((std::same_as<uint8_t, ztl::smallest_unsigned_t<100>>));
  EXPECT_TRUE((std::same_as<uint8_t, ztl::smallest_unsigned_t<255>>));
  EXPECT_TRUE((std::same_as<uint16_t, ztl::smallest_unsigned_t<256>>));
  EXPECT_TRUE((std::same_as<uint16_t, ztl::smallest_unsigned_t<65535>>));
  EXPECT_TRUE((std::same_as<uint32_t, ztl::smallest_unsigned_t<65536>>));
}
