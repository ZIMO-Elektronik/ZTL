#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, logical_not) {
  constexpr auto a{E::A};
  constexpr auto null{a ^ E::A};
  EXPECT_TRUE(!!a);
  EXPECT_FALSE(null);
}
