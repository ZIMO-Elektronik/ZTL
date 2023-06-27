#include "static_list_test.hpp"

TEST_F(StaticListTest, pop_front) {
  // 40 39 38
  List::push_front(_node38);
  List::push_front(_node39);
  List::push_front(_node40);
  EXPECT_EQ(List::front(), 40);

  List::pop_front();
  EXPECT_EQ(List::size(), 2uz);
  EXPECT_EQ(List::front(), 39);

  List::pop_front();
  EXPECT_EQ(List::size(), 1uz);
  EXPECT_EQ(List::front(), 38);

  List::pop_front();
  EXPECT_EQ(List::size(), 0uz);
  EXPECT_TRUE(List::empty());
}
