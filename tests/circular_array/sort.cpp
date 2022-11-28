#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, sort) {
  ztl::circular_array values{2, 10, 4, 5, 1, 7, 8, 9, 3, 6};
  std::ranges::sort(values);
  constexpr ztl::circular_array expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(values, expected);
}
