#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <type_traits>
#include <ztl/explicit_wrapper.hpp>

using G = ztl::explicit_wrapper<int, struct GTag>;

TEST(explicit_wrapper, ctor) {
  { [[maybe_unused]] constexpr auto g{G{}}; }

  { [[maybe_unused]] constexpr auto g{G{100}}; }

  {
    G::value_type i{42};
    [[maybe_unused]] auto g{G{i}};
  }
}

TEST(explicit_wrapper, explicit_conversion) {
  constexpr auto g{G{}};
  G::value_type i{static_cast<G::value_type>(g)};
  static_assert(std::same_as<decltype(i), G::value_type>);
}
