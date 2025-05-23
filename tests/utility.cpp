#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/utility.hpp>

namespace {

struct Adder {
  int op(int v) { return _sum += v; }

private:
  int _sum{};
};

} // namespace

TEST(utility, get) {
  auto is{std::integer_sequence<int, 1, 2, 3>{}};
  static_assert((
    std::same_as<decltype(ztl::get<0uz>(is)), std::integral_constant<int, 1>>));
  static_assert((
    std::same_as<decltype(ztl::get<1uz>(is)), std::integral_constant<int, 2>>));
  static_assert((
    std::same_as<decltype(ztl::get<2uz>(is)), std::integral_constant<int, 3>>));
}

// Convert index sequence to bitmask
TEST(utility, index_sequence2mask) {
  {
    constexpr auto m{ztl::index_sequence2mask(std::make_index_sequence<0uz>{})};
    EXPECT_EQ(m, 0b0u);
  }

  {
    constexpr auto m{ztl::index_sequence2mask(std::make_index_sequence<4uz>{})};
    EXPECT_EQ(m, 0b1111u);
  }

  {
    std::index_sequence<3uz, 5uz> r{};
    auto m{ztl::index_sequence2mask(r)};
    EXPECT_EQ(m, 0b101000);
  }

  {
    std::integer_sequence<size_t, 3uz, 5uz> r{};
    auto m{ztl::index_sequence2mask(r)};
    EXPECT_EQ(m, 0b101000);
  }
}

TEST(utility, make_integer_sequence_from_to) {
  {
    auto s{ztl::make_integer_sequence_from_to<int, 0, 5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, 0, 1, 2, 3, 4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<uint16_t, 2, 5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<uint16_t, 2, 3, 4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -5, 0>()};
    EXPECT_TRUE((std::same_as<decltype(s),
                              std::integer_sequence<int, -5, -4, -3, -2, -1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -5, 2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<int, -5, -4, -3, -2, -1, 0, 1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -0, -5>()};
    EXPECT_TRUE((std::same_as<decltype(s),
                              std::integer_sequence<int, -0, -1, -2, -3, -4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -2, -5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, -2, -3, -4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, 5, 0>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, 5, 4, 3, 2, 1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<size_t, 5, 2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<size_t, 5, 4, 3>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int8_t, -5, -0>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<int8_t, -5, -4, -3, -2, -1>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, -5, -2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s), std::integer_sequence<int, -5, -4, -3>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<int, 2, -5>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<int, 2, 1, 0, -1, -2, -3, -4>>));
  }

  {
    auto s{ztl::make_integer_sequence_from_to<char, 5, -2>()};
    EXPECT_TRUE(
      (std::same_as<decltype(s),
                    std::integer_sequence<char, 5, 4, 3, 2, 1, 0, -1>>));
  }
}

TEST(utility, make_trampoline) {
  {
    Adder add;
    auto f{ztl::make_trampoline(&add, &Adder::op)};

    EXPECT_EQ(42, f(42));
    EXPECT_EQ(142, f(100));
  }

  {
    Adder add;
    auto f{ztl::make_trampoline([add](int v) mutable { return add.op(v); })};

    EXPECT_EQ(42, f(42));
    EXPECT_EQ(142, f(100));
  }
}

TEST(utility, make_trampoline_bind_to_different_instance) {
  {
    auto bind_different_object_no_longer_unique{
      [](Adder& add) { return ztl::make_trampoline(&add, &Adder::op); }};

    Adder add0;
    auto f0{bind_different_object_no_longer_unique(add0)};

    EXPECT_EQ(42, f0(42));
    EXPECT_EQ(142, f0(100));

    Adder add1;
    auto f1{bind_different_object_no_longer_unique(add1)};

    EXPECT_EQ(42, f1(42));
    EXPECT_EQ(142, f1(100));
  }

  {
    auto bind_different_object_no_longer_unique{[](Adder& add) {
      return ztl::make_trampoline([add](int v) mutable { return add.op(v); });
    }};

    Adder add0;
    auto f0{bind_different_object_no_longer_unique(add0)};

    EXPECT_EQ(42, f0(42));
    EXPECT_EQ(142, f0(100));

    Adder add1;
    auto f1{bind_different_object_no_longer_unique(add1)};

    EXPECT_EQ(42, f1(42));
    EXPECT_EQ(142, f1(100));
  }
}
