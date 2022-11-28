#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/limits.hpp>

TEST(limits, smallest_signed) {
  EXPECT_TRUE((std::same_as<int8_t, ztl::smallest_signed_t<-100, 100>>));
  EXPECT_TRUE((std::same_as<int8_t, ztl::smallest_signed_t<-128, 127>>));
  EXPECT_TRUE((std::same_as<int8_t, ztl::smallest_signed_t<-128u, 127>>));
  EXPECT_TRUE((std::same_as<int16_t, ztl::smallest_signed_t<-128, 128>>));
  EXPECT_TRUE((std::same_as<int16_t, ztl::smallest_signed_t<-32768, 32767>>));
  EXPECT_TRUE((std::same_as<int16_t, ztl::smallest_signed_t<-32768u, 32767>>));
  EXPECT_TRUE((std::same_as<int32_t, ztl::smallest_signed_t<-32769, 32767>>));
  EXPECT_TRUE((std::same_as<int32_t, ztl::smallest_signed_t<-70000, 9000000>>));
}
