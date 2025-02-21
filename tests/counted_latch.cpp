#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <optional>
#include <ztl/counted_latch.hpp>

namespace {

enum class E { _0, _1 };

} // namespace

TEST(counted_latch, ctor) {
  {
    ztl::counted_latch<E, 8uz> cl;
    EXPECT_EQ(cl, E::_0);
  }

  {
    ztl::counted_latch<E, 2uz> cl{E::_1};
    EXPECT_EQ(cl, E::_1);
  }

  {
    struct S {
      S(int i) : _i{i} {}
      int _i;
      auto operator<=>(S const&) const = default;
    };

    ztl::counted_latch<S, 8uz> cl{S{10}};
    S s{cl};
    EXPECT_EQ(s._i, 10);
  }
}

TEST(counted_latch, set) {
  // Latching 8 times should yield the new value
  {
    ztl::counted_latch<E, 8uz> cl;
    cl.set(E::_1); // 1
    cl.set(E::_1); // 2
    cl.set(E::_1); // 3
    cl.set(E::_1); // 4
    cl.set(E::_1); // 5
    cl.set(E::_1); // 6
    cl.set(E::_1); // 7
    cl.set(E::_1); // 8
    EXPECT_EQ(cl, E::_1);
  }

  // Latching only 7 times won't yield the new value
  {
    ztl::counted_latch<E, 8uz> cl;
    cl.set(E::_1); // 1
    cl.set(E::_1); // 2
    cl.set(E::_1); // 3
    cl.set(E::_1); // 4
    cl.set(E::_1); // 5
    cl.set(E::_1); // 6
    cl.set(E::_1); // 7
    EXPECT_EQ(cl, E::_0);
  }

  // Latching a new value 4 times, then the old one once, and the new one 3
  // times again won't yield the new value
  {
    ztl::counted_latch<E, 8uz> cl;
    cl.set(E::_1); // 1
    cl.set(E::_1); // 2
    cl.set(E::_1); // 3
    cl.set(E::_1); // 4
    cl.set(E::_0); // 5
    cl.set(E::_1); // 6
    cl.set(E::_1); // 7
    cl.set(E::_1); // 8
    EXPECT_EQ(cl, E::_0);
  }

  // Latching 8 times should yield the new value, latching the old one only 4
  // times afterwards won't change that
  {
    ztl::counted_latch<E, 8uz> cl;
    cl.set(E::_1); // 1
    cl.set(E::_1); // 2
    cl.set(E::_1); // 3
    cl.set(E::_1); // 4
    cl.set(E::_1); // 5
    cl.set(E::_1); // 6
    cl.set(E::_1); // 7
    cl.set(E::_1); // 8
    cl.set(E::_0); // 1
    cl.set(E::_0); // 2
    cl.set(E::_0); // 3
    cl.set(E::_0); // 4
    EXPECT_EQ(cl, E::_1);
  }

  // Latching combined with an optional
  {
    ztl::counted_latch<std::optional<int>, 3u> cl{};
    cl.set(42);
    EXPECT_FALSE(cl.value());
    cl.set(42);
    EXPECT_FALSE(cl.value());
    cl.set(42);
    EXPECT_TRUE(cl.value());
    EXPECT_EQ(cl.value(), 42);
    cl.set({});
    EXPECT_TRUE(cl.value());
    EXPECT_EQ(cl.value(), 42);
    cl.set({});
    EXPECT_TRUE(cl.value());
    EXPECT_EQ(cl.value(), 42);
    cl.set({});
    EXPECT_FALSE(cl.value());
    EXPECT_EQ(cl.value(), std::optional<int>{});
  }
}
