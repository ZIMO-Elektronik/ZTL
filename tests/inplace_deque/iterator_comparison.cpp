#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_deque.hpp>

TEST(inplace_deque, iterator_comparison) {
  {
    ztl::inplace_deque<int, 5uz> c{1, 2, 3};
    EXPECT_TRUE(cbegin(c) < cend(c));
    EXPECT_FALSE(cend(c) < cbegin(c));
  }

  {
    ztl::inplace_deque<int, 5uz> c;
    c.push_front(1);
    c.push_back(2);
    c.push_back(3);
    c.push_back(4);
    auto first{begin(c)};
    auto last{end(c)};
    EXPECT_TRUE(cbegin(c) < cend(c));
    EXPECT_FALSE(cend(c) < cbegin(c));
  }
}
