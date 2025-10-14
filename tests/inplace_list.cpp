#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_list.hpp>

using t_list = ztl::inplace_list<int, 5uz>;

TEST(inplace_list, ctor) {
  ztl::inplace_list<int, 1uz> default_ctor;
  EXPECT_EQ(size(default_ctor), 0uz);

  ztl::inplace_list<int, 5uz> variadic_ctor{1, 2, 3};
  EXPECT_EQ(variadic_ctor.front(), 1);
  EXPECT_EQ(variadic_ctor.back(), 3);
  EXPECT_EQ(size(variadic_ctor), 3uz);
  EXPECT_EQ(variadic_ctor.max_size(), 5uz);

  ztl::inplace_list variadic_ctor_ctad{1, 2, 3};
  EXPECT_EQ(variadic_ctor_ctad.front(), 1);
  EXPECT_EQ(variadic_ctor_ctad.back(), 3);
  EXPECT_EQ(size(variadic_ctor_ctad), 3uz);
  EXPECT_EQ(variadic_ctor_ctad.max_size(), 3uz);

  ztl::inplace_list copy_ctor{variadic_ctor};
  EXPECT_EQ(copy_ctor.front(), 1);
  EXPECT_EQ(copy_ctor.back(), 3);
  EXPECT_EQ(size(copy_ctor), 3uz);
  EXPECT_EQ(copy_ctor.max_size(), 5uz);
}

TEST(inplace_list, empty) {
  ztl::inplace_list<int, 2uz> list;
  EXPECT_TRUE(empty(list));

  list.push_back(1);
  EXPECT_FALSE(empty(list));
}

TEST(inplace_list, full) {
  ztl::inplace_list list{1, 2, 3};
  EXPECT_TRUE(full(list));

  list.pop_back();
  EXPECT_FALSE(full(list));
}

TEST(inplace_list, size) {
  ztl::inplace_list<int, 5uz> list{1, 2, 3, 4};
  EXPECT_EQ(size(list), 4);

  list.pop_back();
  EXPECT_EQ(size(list), 3);
}

TEST(inplace_list, front) {
  ztl::inplace_list list{1, 2, 3};

  ASSERT_EQ(list.front(), 1);
}

TEST(inplace_list, back) {
  ztl::inplace_list list{1, 2, 3};
  ASSERT_EQ(list.back(), 3);
}

TEST(inplace_list, insert) {
  ztl::inplace_list<int, 5uz> list{1, 2, 3};
  list.insert(++begin(list), 4);

  ztl::inplace_list expected{1, 4, 2, 3};
  ASSERT_TRUE(std::ranges::equal(list, expected));
}

TEST(inplace_list, erase) {
  ztl::inplace_list list{1, 2, 3, 4};
  list.erase(++begin(list));

  ztl::inplace_list expected{1, 3, 4};
  ASSERT_TRUE(std::ranges::equal(list, expected));
}

TEST(inplace_list, move) {
  ztl::inplace_list list{1, 2, 3, 4};
  list.move(begin(list), end(list));

  ASSERT_TRUE(std::ranges::equal(list, ztl::inplace_list{2, 3, 4, 1}));
}

TEST(inplace_list, move_same_pos) {
  ztl::inplace_list list{1, 2, 3, 4};
  list.move(begin(list), begin(list));

  ASSERT_TRUE(std::ranges::equal(list, ztl::inplace_list{1, 2, 3, 4}));
}

TEST(inplace_list, push_front) {
  ztl::inplace_list<int, 5uz> list{1, 2, 3};
  list.push_front(4);

  ztl::inplace_list expected{4, 1, 2, 3};
  ASSERT_TRUE(std::ranges::equal(list, expected));
}

TEST(inplace_list, push_back) {
  ztl::inplace_list<int, 5uz> list{1, 2, 3};
  list.push_back(4);

  ztl::inplace_list expected{1, 2, 3, 4};
  ASSERT_TRUE(std::ranges::equal(list, expected));
}

TEST(inplace_list, pop_front) {
  ztl::inplace_list list{1, 2, 3, 4};
  list.pop_front();

  ztl::inplace_list expected{2, 3, 4};
  ASSERT_TRUE(std::ranges::equal(list, expected));
}

TEST(inplace_list, pop_back) {
  ztl::inplace_list list{1, 2, 3, 4};
  list.pop_back();

  ztl::inplace_list expected{1, 2, 3};
  ASSERT_TRUE(std::ranges::equal(list, expected));
}

TEST(inplace_list, spaceship) {
  t_list list{1, 2, 3, 4};

  t_list equal{list};
  EXPECT_TRUE((list <=> equal) == 0);
  EXPECT_TRUE((equal <=> list) == 0);
  EXPECT_TRUE(list == equal);

  t_list lesser{1, 2, 2, 4};
  EXPECT_TRUE((list <=> lesser) > 0);
  EXPECT_TRUE((lesser <=> list) < 0);
  EXPECT_FALSE(list == lesser);

  t_list greater{1, 2, 4, 4};
  EXPECT_TRUE((list <=> greater) < 0);
  EXPECT_TRUE((greater <=> list) > 0);
  EXPECT_FALSE(list == greater);

  t_list shorter{1, 2, 3};
  EXPECT_TRUE((list <=> shorter) > 0);
  EXPECT_TRUE((shorter <=> list) < 0);
}

TEST(inplace_list, integrity) {
  t_list list{1, 2, 3, 4, 5};

  list.erase(++begin(list));
  t_list erased{1, 3, 4, 5};
  EXPECT_EQ(list, erased);

  list.push_back(2);
  t_list pushed{1, 3, 4, 5, 2};
  EXPECT_EQ(list, pushed);
}
