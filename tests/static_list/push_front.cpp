#include "static_list_test.hpp"

TEST_F(StaticListTest, push_front) {
  // 40 39 38
  List::push_front(node38);
  List::push_front(node39);
  List::push_front(node40);

  auto it{List::begin()};
  EXPECT_EQ(*it++, 40);
  EXPECT_EQ(*it++, 39);
  EXPECT_EQ(*it, 38);

  EXPECT_EQ(List::front(), 40);
  EXPECT_EQ(List::back(), 38);

  EXPECT_EQ(List::size(), 3uz);
}
