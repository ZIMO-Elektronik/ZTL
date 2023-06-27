#include "static_list_test.hpp"

TEST_F(StaticListTest, pop_back) {
  // 44 45 46
  List::push_back(_node44);
  List::push_back(_node45);
  List::push_back(_node46);
  EXPECT_EQ(List::back(), 46);

  List::pop_back();
  EXPECT_EQ(List::size(), 2uz);
  EXPECT_EQ(List::back(), 45);

  List::pop_back();
  EXPECT_EQ(List::size(), 1uz);
  EXPECT_EQ(List::back(), 44);

  List::pop_back();
  EXPECT_EQ(List::size(), 0uz);
  EXPECT_TRUE(List::empty());

  List::clear();
}
