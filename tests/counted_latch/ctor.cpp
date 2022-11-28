#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/counted_latch.hpp>

TEST(counted_latch, ctor) {
  enum class E { _0, _1 };

  {
    ztl::counted_latch<E, 8uz> cl;
    E e{cl};
    EXPECT_EQ(E::_0, e);
  }

  {
    ztl::counted_latch<E, 2uz> cl{E::_1};
    E e{cl};
    EXPECT_EQ(E::_1, e);
  }

  {
    struct S {
      S(int i) : i_{i} {}
      int i_;
      auto operator<=>(S const&) const = default;
    };

    ztl::counted_latch<S, 8uz> cl{S{10}};
    S s{cl};
    EXPECT_EQ(10, s.i_);
  }
}
