#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/enum.hpp>

namespace {

enum class E { A = 1 << 0, B = 1 << 1, C = 1 << 2, D = 1 << 3, E = -42 };

ZTL_MAKE_ENUM_CLASS_FLAGS(E)

} // namespace

TEST(enum, operator_and) {
  constexpr auto ab{E::B | E::A};
  constexpr auto cd{E::D | E::C};
  EXPECT_EQ(ab & E::B, E::B);
  EXPECT_EQ(ab & E::A, E::A);
  EXPECT_EQ(cd & E::D, E::D);
}

TEST(enum, operator_assign_and) {
  auto ab{E::C | E::B | E::A};
  ab &= E::C;
  EXPECT_EQ(std::to_underlying(ab), 0b100);
}

TEST(enum, operator_assign_or) {
  auto abc{E::A | E::B};
  abc |= E::C;
  EXPECT_EQ(std::to_underlying(abc), 0b111);
}

TEST(enum, operator_assign_xor) {
  auto ab{E::C | E::B | E::A};
  ab ^= E::C;
  EXPECT_EQ(std::to_underlying(ab), 0b11);
}

TEST(enum, operator_complement) {
  constexpr auto abc{E::C | E::B | E::A};
  constexpr auto d{~abc};
  EXPECT_EQ(std::to_underlying(d), 0b11111111'11111111'11111111'11111000);
}

TEST(enum, logical_not) {
  constexpr auto a{E::A};
  constexpr auto null{a ^ E::A};
  EXPECT_TRUE(!!a);
  EXPECT_FALSE(null);
}

TEST(enum, operator_or) {
  constexpr auto a{E::A};
  constexpr auto b{E::B};
  constexpr auto c{E::C};
  constexpr auto db{E::D | E::B};
  EXPECT_EQ(std::to_underlying(b | a), 0b11);
  EXPECT_EQ(std::to_underlying(c | a), 0b101);
  EXPECT_EQ(std::to_underlying(db), 0b1010);
}

TEST(enum, unary_minus) {
  EXPECT_EQ(-E::B, -2);
  EXPECT_EQ(-E::E, 42);
}

TEST(enum, unary_plus) {
  EXPECT_EQ(+E::B, 2);
  EXPECT_EQ(+E::E, -42);
}

TEST(enum, operator_xor) {
  constexpr auto ab{E::B | E::A};
  constexpr auto a{E::B ^ E::B ^ E::A};
  EXPECT_EQ(a, E::A);
  EXPECT_EQ(ab ^ E::A, E::B);
}
