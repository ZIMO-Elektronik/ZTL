#include "static_list_test.hpp"

TEST_F(StaticListTest, clear) {
  List::push_back(_node44);
  List::push_back(_node45);
  List::push_back(_node46);

  EXPECT_EQ(List::size(), 3uz);

  List::clear();

  EXPECT_EQ(List::size(), 0uz);
}
