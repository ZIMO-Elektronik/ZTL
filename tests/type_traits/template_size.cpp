#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

template<typename... Ts>
struct S : std::tuple<Ts...> {
  S(Ts... ts) : std::tuple<Ts...>{ts...} {}
};

// Get size of arbitrary sequence type
TEST(type_traits, template_size) {
  auto t0{std::make_tuple(1, 2, 3, 4, 5)};
  S s0{1337, 42.42, "hello world"};
  auto p0{std::make_pair(42, 43)};

  EXPECT_EQ(5, (ztl::template_size_v<decltype(t0)>));
  EXPECT_EQ(3, (ztl::template_size_v<decltype(s0)>));
  EXPECT_EQ(2, (ztl::template_size_v<decltype(p0)>));
}
