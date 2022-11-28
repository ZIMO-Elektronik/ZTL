#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/array.hpp>

TEST(array, make_array) {
  constexpr auto a{ztl::make_array<double>([](double d) { return d * d; },
                                           std::make_index_sequence<11uz>{})};
  constexpr std::array b{
    0.0, 1.0, 4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0, 81.0, 100.0};
  EXPECT_EQ(a, b);
}
