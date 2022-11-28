#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, operator_complement) {
  constexpr auto abc{E::C | E::B | E::A};
  constexpr auto d{~abc};
  EXPECT_EQ(std::to_underlying(d), 0b11111111'11111111'11111111'11111000);
}
