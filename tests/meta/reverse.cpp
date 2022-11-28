#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/meta.hpp>

// Create reverse sequence
TEST(meta, reverse_sequence) {
  auto t0{std::make_tuple(42, "aha!", 'c')};
  auto rt0{ztl::reverse(t0)};
  EXPECT_TRUE(
    (std::same_as<std::tuple<char, char const*, int>, decltype(rt0)>));
}
