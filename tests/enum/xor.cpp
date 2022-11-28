#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, operator_xor) {
  constexpr auto ab{E::B | E::A};
  constexpr auto a{E::B ^ E::B ^ E::A};
  EXPECT_EQ(a, E::A);
  EXPECT_EQ(ab ^ E::A, E::B);
}
