#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

TEST(circular_array, iterator_arithmetic_addition) {
  ztl::circular_array c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  c.pop_front();
  c.push_back(10);

  // begin points to index 1
  // end points to index 10
  auto it{begin(c)};
  EXPECT_EQ(*(it + 0), 1);
  EXPECT_EQ(*(it + 1), 2);
  EXPECT_EQ(*(it + 2), 3);
  EXPECT_EQ(*(it + 3), 4);
  EXPECT_EQ(*(it + 4), 5);
  EXPECT_EQ(*(it + 5), 6);
  EXPECT_EQ(*(it + 6), 7);
  EXPECT_EQ(*(it + 7), 8);
  EXPECT_EQ(*(it + 8), 9);
  EXPECT_EQ(*(it + 9), 10);
  EXPECT_EQ(*(it + 10), 0);
  EXPECT_EQ(*(it + 11), 1);
  EXPECT_EQ(*(it + 12), 2);
  EXPECT_EQ(*(it + 13), 3);
  EXPECT_EQ(*(it + 14), 4);
  EXPECT_EQ(*(it + 15), 5);
  EXPECT_EQ(*(it + 16), 6);
  EXPECT_EQ(*(it + 17), 7);
  EXPECT_EQ(*(it + 18), 8);
  EXPECT_EQ(*(it + 19), 9);
  EXPECT_EQ(*(it + 20), 10);
  EXPECT_EQ(*(it + 21), 0);
}

TEST(circular_array, iterator_arithmetic_negative_addition) {
  ztl::circular_array<int, 10uz> c;
  c.push_front(10);
  c.push_front(9);
  c.push_front(8);
  c.push_front(7);
  c.pop_front();
  c.push_back(0);
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  c.push_back(4);
  c.push_back(5);
  c.push_back(6);

  // begin points to index 8
  // end points to index 7
  auto it{begin(c)};
  EXPECT_EQ(*(it + -1), 7);
  EXPECT_EQ(*(it + -2), 6);
  EXPECT_EQ(*(it + -3), 5);
  EXPECT_EQ(*(it + -4), 4);
  EXPECT_EQ(*(it + -5), 3);
  EXPECT_EQ(*(it + -6), 2);
  EXPECT_EQ(*(it + -7), 1);
  EXPECT_EQ(*(it + -8), 0);
  EXPECT_EQ(*(it + -9), 10);
  EXPECT_EQ(*(it + -10), 9);
  EXPECT_EQ(*(it + -11), 8);
  EXPECT_EQ(*(it + -12), 7);
  EXPECT_EQ(*(it + -13), 6);
  EXPECT_EQ(*(it + -14), 5);
  EXPECT_EQ(*(it + -15), 4);
  EXPECT_EQ(*(it + -16), 3);
  EXPECT_EQ(*(it + -17), 2);
  EXPECT_EQ(*(it + -18), 1);
  EXPECT_EQ(*(it + -19), 0);
  EXPECT_EQ(*(it + -20), 10);
  EXPECT_EQ(*(it + -21), 9);
}

TEST(circular_array, iterator_arithmetic_subtraction) {
  ztl::circular_array c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  c.pop_front();
  c.push_back(10);

  // begin points to index 1
  // end points to index 10
  auto it{begin(c)};
  EXPECT_EQ(*(it - 0), 1);
  EXPECT_EQ(*(it - 1), 0);
  EXPECT_EQ(*(it - 2), 10);
  EXPECT_EQ(*(it - 3), 9);
  EXPECT_EQ(*(it - 4), 8);
  EXPECT_EQ(*(it - 5), 7);
  EXPECT_EQ(*(it - 6), 6);
  EXPECT_EQ(*(it - 7), 5);
  EXPECT_EQ(*(it - 8), 4);
  EXPECT_EQ(*(it - 9), 3);
  EXPECT_EQ(*(it - 10), 2);
  EXPECT_EQ(*(it - 11), 1);
  EXPECT_EQ(*(it - 12), 0);
  EXPECT_EQ(*(it - 13), 10);
  EXPECT_EQ(*(it - 14), 9);
  EXPECT_EQ(*(it - 15), 8);
  EXPECT_EQ(*(it - 16), 7);
  EXPECT_EQ(*(it - 17), 6);
  EXPECT_EQ(*(it - 18), 5);
  EXPECT_EQ(*(it - 19), 4);
  EXPECT_EQ(*(it - 20), 3);
  EXPECT_EQ(*(it - 21), 2);
}

TEST(circular_array, iterator_arithmetic_negative_subtraction) {
  ztl::circular_array<int, 10uz> c;
  c.push_front(10);
  c.push_front(9);
  c.push_front(8);
  c.push_front(7);
  c.pop_front();
  c.push_back(0);
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  c.push_back(4);
  c.push_back(5);
  c.push_back(6);

  // begin points to index 8
  // end points to index 7
  auto it{cend(c)};
  EXPECT_EQ(*(it - -1), 8);
  EXPECT_EQ(*(it - -2), 9);
  EXPECT_EQ(*(it - -3), 10);
  EXPECT_EQ(*(it - -4), 0);
  EXPECT_EQ(*(it - -5), 1);
  EXPECT_EQ(*(it - -6), 2);
  EXPECT_EQ(*(it - -7), 3);
  EXPECT_EQ(*(it - -8), 4);
  EXPECT_EQ(*(it - -9), 5);
  EXPECT_EQ(*(it - -10), 6);
  EXPECT_EQ(*(it - -11), 7);
  EXPECT_EQ(*(it - -12), 8);
  EXPECT_EQ(*(it - -13), 9);
  EXPECT_EQ(*(it - -14), 10);
  EXPECT_EQ(*(it - -15), 0);
  EXPECT_EQ(*(it - -16), 1);
  EXPECT_EQ(*(it - -17), 2);
  EXPECT_EQ(*(it - -18), 3);
  EXPECT_EQ(*(it - -19), 4);
  EXPECT_EQ(*(it - -20), 5);
  EXPECT_EQ(*(it - -21), 6);
}

#define EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(b, a, n)                         \
  do {                                                                         \
    EXPECT_EQ((b) - (a), n);                                                   \
    EXPECT_EQ((b), (a) + ((b) - (a)));                                         \
  } while (0);

TEST(circular_array, iterator_difference_read_index_less_or_equal_write_index) {
  ztl::circular_array c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  c.pop_front();
  c.push_back(10);
  c.pop_back();
  c.pop_back();

  // begin points to index 1
  // end points to index 9
  auto it{begin(c)};
  EXPECT_EQ(it - it, 0);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it, 0);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 1, -1)
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 2, -2);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 3, -3);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 4, -4);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 5, -5);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 6, -6);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 7, -7);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 8, -8);
  EXPECT_EQ(it + 8, end(c));

  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 1, it, 1);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 2, it, 2);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 3, it, 3);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 4, it, 4);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 5, it, 5);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 6, it, 6);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 7, it, 7);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it + 8, it, 8);
  EXPECT_EQ(it + 8, end(c));

  it = end(c);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 1, 1);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 2, 2);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 3, 3);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 4, 4);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 5, 5);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 6, 6);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 7, 7);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 8, 8);
  EXPECT_EQ(it - 8, begin(c));

  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 1, it, -1);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 2, it, -2);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 3, it, -3);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 4, it, -4);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 5, it, -5);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 6, it, -6);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 7, it, -7);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it - 8, it, -8);
  EXPECT_EQ(it - 8, begin(c));
}

TEST(circular_array, iterator_difference_read_index_greater_write_index) {
  ztl::circular_array<int, 10uz> c;
  c.push_front(10);
  c.push_front(9);
  c.push_front(8);

  c.push_back(0);
  c.push_back(1);
  c.push_back(2);

  // begin points to index 8
  // end points to index 3
  auto it{begin(c)};
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it, 0);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 1, -1);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 2, -2);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 3, -3);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 4, -4);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 5, -5);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it + 6, -6);
  EXPECT_EQ(it + 6, end(c));

  it = end(c);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 1, 1);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 2, 2);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 3, 3);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 4, 4);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 5, 5);
  EXPECT_EQ_IT_DIFF_CHECK_POSTCONDITION(it, it - 6, 6);
  EXPECT_EQ(it - 6, begin(c));
}