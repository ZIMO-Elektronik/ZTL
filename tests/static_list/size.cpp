#include "static_list_test.hpp"

TEST_F(StaticListTest, size) {
  EXPECT_EQ(List::size(), 0uz);
  List::push_back(node38);
  EXPECT_EQ(List::size(), 1uz);
  List::push_back(node39);
  EXPECT_EQ(List::size(), 2uz);
  List::push_back(node40);
  EXPECT_EQ(List::size(), 3uz);
}
