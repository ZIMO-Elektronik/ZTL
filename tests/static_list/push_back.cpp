#include "static_list_test.hpp"

TEST_F(StaticListTest, push_back) {
  // 44 45 46
  List::push_back(_node44);
  List::push_back(_node45);
  List::push_back(_node46);

  auto it{List::begin()};
  EXPECT_EQ(*it++, 44);
  EXPECT_EQ(*it++, 45);
  EXPECT_EQ(*it, 46);

  EXPECT_EQ(List::front(), 44);
  EXPECT_EQ(List::back(), 46);

  EXPECT_EQ(List::size(), 3uz);
}
