#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, iterator_decrement) {
  {
    ztl::circular_array c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    c.pop_front();
    c.push_back(10);

    auto it{begin(c)};
    EXPECT_EQ(*it--, 1);
    EXPECT_EQ(*it--, 0);
    EXPECT_EQ(*it--, 10);
    EXPECT_EQ(*it--, 9);
    EXPECT_EQ(*it--, 8);
    EXPECT_EQ(*it--, 7);
    EXPECT_EQ(*it--, 6);
    EXPECT_EQ(*it--, 5);
    EXPECT_EQ(*it--, 4);
    EXPECT_EQ(*it--, 3);
    EXPECT_EQ(*it--, 2);
    EXPECT_EQ(*it--, 1);
  }

  {
    ztl::circular_array c{0, 1, 2, 3, 4, 5, 6};
    c.pop_front();
    c.push_back(7);

    auto it{begin(c)};
    EXPECT_EQ(*it--, 1);
    EXPECT_EQ(*it--, 0);
    EXPECT_EQ(*it--, 7);
    EXPECT_EQ(*it--, 6);
    EXPECT_EQ(*it--, 5);
    EXPECT_EQ(*it--, 4);
    EXPECT_EQ(*it--, 3);
    EXPECT_EQ(*it--, 2);
    EXPECT_EQ(*it--, 1);
  }
}
