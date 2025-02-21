#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>
#include <ztl/delayed_latch.hpp>

using namespace std::chrono_literals;

namespace {

class DelayedLatchTest : public ::testing::Test {
protected:
  DelayedLatchTest() {}
  virtual ~DelayedLatchTest() {}

  enum E { _0, _1 };

  template<typename Rep, typename Period>
  void SetFor(E e, std::chrono::duration<Rep, Period> duration) {
    auto const then{std::chrono::system_clock::now() + duration};
    while (std::chrono::system_clock::now() < then) _dl.set(e);
  }

  ztl::delayed_latch<E, std::chrono::milliseconds> _dl{E::_0, 100ms};
};

} // namespace

TEST_F(DelayedLatchTest, ctor) { EXPECT_EQ(_dl, E::_0); }

TEST_F(DelayedLatchTest, set_long_enough_to_latch) {
  SetFor(E::_1, 50ms);
  EXPECT_EQ(_dl, E::_0);
  SetFor(E::_1, 100ms);
  EXPECT_EQ(_dl, E::_1);
}

TEST_F(DelayedLatchTest, dont_set_long_enough_to_latch) {
  SetFor(E::_1, 50ms);
  EXPECT_EQ(_dl, E::_0);
  SetFor(E::_0, 1ms);
  EXPECT_EQ(_dl, E::_0);
  SetFor(E::_1, 50ms);
  EXPECT_EQ(_dl, E::_0);
}