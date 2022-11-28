#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

template<typename... Ts>
struct S : std::tuple<Ts...> {
  S() = default;
  S(Ts... ts) : std::tuple<Ts...>{ts...} {}
};

// Use template type to create new type
TEST(type_traits, template_t) {
  S s0{42, 43, "wtf"};
  ztl::template_t<decltype(s0), char, float> s1{};
  auto t0{std::make_tuple('c', 42)};
  ztl::template_t<decltype(t0), char, char> t1{};

  EXPECT_TRUE((std::same_as<S<char, float>, decltype(s1)>));
  EXPECT_TRUE((std::same_as<std::tuple<char, char>, decltype(t1)>));
}
