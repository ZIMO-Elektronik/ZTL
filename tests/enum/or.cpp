#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, operator_or) {
  constexpr auto a{E::A};
  constexpr auto b{E::B};
  constexpr auto c{E::C};
  constexpr auto db{E::D | E::B};
  EXPECT_EQ(std::to_underlying(b | a), 0b11);
  EXPECT_EQ(std::to_underlying(c | a), 0b101);
  EXPECT_EQ(std::to_underlying(db), 0b1010);
}
