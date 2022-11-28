#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, operator_assign_xor) {
  auto ab{E::C | E::B | E::A};
  ab ^= E::C;
  EXPECT_EQ(std::to_underlying(ab), 0b11);
}
