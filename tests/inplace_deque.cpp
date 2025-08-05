#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <numeric>
#include <ztl/inplace_deque.hpp>

namespace {

struct S {
  void add(int value) { _deque.push_back(value); }
  int sum() const { return std::accumulate(cbegin(_deque), cend(_deque), 0); }

private:
  ztl::inplace_deque<int, 10uz> _deque;
};

} // namespace

TEST(inplace_deque, const_correctness) {
  S s;
  s.add(1);
  s.add(2);
  s.add(3);
  s.add(4);
  EXPECT_EQ(s.sum(), 10);
}

TEST(inplace_deque, ctor) {
  ztl::inplace_deque<int, 1uz> default_ctor;
  EXPECT_EQ(size(default_ctor), 0uz);

  ztl::inplace_deque<int, 5uz> variadic_ctor{1, 2, 3};
  EXPECT_EQ(variadic_ctor.front(), 1);
  EXPECT_EQ(variadic_ctor.back(), 3);
  EXPECT_EQ(size(variadic_ctor), 3uz);
  EXPECT_EQ(variadic_ctor.max_size(), 5uz);

  ztl::inplace_deque variadic_ctor_ctad{1, 2, 3};
  EXPECT_EQ(variadic_ctor_ctad.front(), 1);
  EXPECT_EQ(variadic_ctor_ctad.back(), 3);
  EXPECT_EQ(size(variadic_ctor_ctad), 3uz);
  EXPECT_EQ(variadic_ctor_ctad.max_size(), 3uz);
}

TEST(inplace_deque, empty) {
  ztl::inplace_deque<int, 3uz> c;
  EXPECT_TRUE(c.empty());
  EXPECT_TRUE(empty(c));

  c.push_back(5);
  EXPECT_FALSE(c.empty());
  EXPECT_FALSE(empty(c));

  c.pop_back();
  EXPECT_TRUE(c.empty());
  EXPECT_TRUE(empty(c));

  // Trying to remove further elements causes undefined behavior
  EXPECT_DEATH(c.pop_back(), "");
}

TEST(inplace_deque, full) {
  ztl::inplace_deque<int, 4uz> c;
  EXPECT_TRUE(c.empty());
  EXPECT_TRUE(empty(c));

  // Push till full
  c.push_back(0);
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  EXPECT_TRUE(c.full());
  EXPECT_TRUE(full(c));

  // Removing one element
  c.pop_back();
  EXPECT_FALSE(c.full());
  EXPECT_FALSE(full(c));

  // Adding one element
  c.push_back(4);
  EXPECT_EQ(c.back(), 4);
  EXPECT_TRUE(c.full());
  EXPECT_TRUE(full(c));

  // Trying to add further elements causes undefined behavior
  EXPECT_DEATH(c.push_back(42), "");
}

// const_iterator can be constructed and assigned from iterator
TEST(inplace_deque, implicit_conversion_iterator2const_iterator) {
  ztl::inplace_deque<int, 1uz>::iterator iterator;
  ztl::inplace_deque<int, 1uz>::const_iterator const_iterator{iterator};
  const_iterator = iterator;
}

TEST(inplace_deque, iterator_arithmetic_addition) {
  ztl::inplace_deque c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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

TEST(inplace_deque, iterator_arithmetic_negative_addition) {
  ztl::inplace_deque<int, 10uz> c;
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

TEST(inplace_deque, iterator_arithmetic_subtraction) {
  ztl::inplace_deque c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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

TEST(inplace_deque, iterator_arithmetic_negative_subtraction) {
  ztl::inplace_deque<int, 10uz> c;
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

TEST(inplace_deque, iterator_difference_read_index_less_or_equal_write_index) {
  ztl::inplace_deque c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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

TEST(inplace_deque, iterator_difference_read_index_greater_write_index) {
  ztl::inplace_deque<int, 10uz> c;
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

TEST(inplace_deque, iterator_decrement) {
  {
    ztl::inplace_deque c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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
    ztl::inplace_deque c{0, 1, 2, 3, 4, 5, 6};
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

TEST(inplace_deque, iterator_increment) {
  ztl::inplace_deque c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  c.pop_front();
  c.push_back(10);

  auto it{begin(c)};
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 6);
  EXPECT_EQ(*it++, 7);
  EXPECT_EQ(*it++, 8);
  EXPECT_EQ(*it++, 9);
  EXPECT_EQ(*it++, 10);
  EXPECT_EQ(*it++, 0);
  EXPECT_EQ(*it++, 1);
}

TEST(inplace_deque, resize) {
  ztl::inplace_deque<int, 10uz> c;
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
  EXPECT_EQ(size(c), 10uz);
  c.resize(5uz);
  EXPECT_EQ(size(c), 5uz);
}

TEST(inplace_deque, size) {
  ztl::inplace_deque<int, 10uz> c;
  EXPECT_EQ(0uz, size(c));

  c.push_back(42);
  EXPECT_EQ(1uz, size(c));

  c.pop_back();
  EXPECT_EQ(0uz, size(c));

  c.push_front(43);
  EXPECT_EQ(1uz, size(c));
}

TEST(inplace_deque, sort) {
  {
    ztl::inplace_deque values{2, 10, 4, 5, 1, 7, 8, 9, 3, 6};
    std::ranges::sort(values);
    constexpr ztl::inplace_deque expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(values, expected);
  }

  {
    ztl::inplace_deque<int, 10uz> values;
    values.push_back(2);
    values.push_back(10);
    values.push_back(4);
    values.push_back(5);
    values.push_back(1);
    values.push_front(7);
    values.push_front(6);
    values.push_front(3);
    values.push_front(9);
    values.push_front(8);
    std::ranges::sort(values);
    constexpr ztl::inplace_deque expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(values, expected);
  }
}

TEST(inplace_deque, traits) {
  using inplace_deque = ztl::inplace_deque<int, 1uz>;
  using iterator = inplace_deque::iterator;
  using const_iterator = inplace_deque::const_iterator;
  static_assert(std::ranges::random_access_range<inplace_deque>);
  static_assert(std::random_access_iterator<iterator>);
  static_assert(std::is_copy_constructible_v<iterator>);
  static_assert(std::is_copy_constructible_v<const_iterator>);
  static_assert(std::is_trivially_copy_constructible_v<iterator>);
  static_assert(std::is_trivially_copy_constructible_v<const_iterator>);
}

TEST(inplace_deque, three_way_comparison) {
  ztl::inplace_deque<int, 10uz> a, b, c;

  a.push_back(1);
  a.push_back(2);
  a.push_back(3);

  b.push_front(3);
  b.push_front(2);
  b.push_front(1);

  c.push_back(1);
  c.push_back(2);
  c.push_back(4);

  // ==
  EXPECT_TRUE((a <=> b) == 0);
  EXPECT_TRUE(a == b);

  // <
  EXPECT_TRUE((a <=> c) < 0);
  EXPECT_FALSE(a == c);

  // >
  EXPECT_TRUE((c <=> a) > 0);
  EXPECT_FALSE(c == a);

  // Prefix comparison: d = [1, 2]
  ztl::inplace_deque<int, 10uz> d;
  d.push_back(1);
  d.push_back(2);

  EXPECT_TRUE((d <=> a) < 0);
  EXPECT_TRUE((a <=> d) > 0);

  // Reverse order: e = [3, 2, 1]
  ztl::inplace_deque<int, 10uz> e;
  e.push_front(1);
  e.push_front(2);
  e.push_front(3);

  EXPECT_TRUE((e <=> a) > 0); // [3,2,1] > [1,2,3] lexicographically
  EXPECT_FALSE(e == a);
}
