#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <numeric>
#include <ztl/circular_array.hpp>

struct S {
  void add(int value) { _ca.push_back(value); }
  int sum() const { return std::accumulate(cbegin(_ca), cend(_ca), 0); }

private:
  ztl::circular_array<int, 10uz> _ca;
};

TEST(circular_array, const_correctness) {
  S s;
  s.add(1);
  s.add(2);
  s.add(3);
  s.add(4);
  EXPECT_EQ(s.sum(), 10);
}
