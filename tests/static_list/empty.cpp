#include "static_list_test.hpp"

TEST_F(StaticListTest, empty) {
  EXPECT_TRUE(List::empty());
  List::push_back(_node38);
  EXPECT_FALSE(List::empty());
}
