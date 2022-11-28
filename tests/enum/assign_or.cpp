#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, operator_assign_or) {
  auto abc{E::A | E::B};
  abc |= E::C;
  EXPECT_EQ(std::to_underlying(abc), 0b111);
}
