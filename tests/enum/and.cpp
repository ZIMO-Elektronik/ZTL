#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, operator_and) {
  constexpr auto ab{E::B | E::A};
  constexpr auto cd{E::D | E::C};
  EXPECT_EQ(ab & E::B, E::B);
  EXPECT_EQ(ab & E::A, E::A);
  EXPECT_EQ(cd & E::D, E::D);
}
