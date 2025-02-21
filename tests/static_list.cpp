#include <gtest/gtest.h>
#include <ztl/static_list.hpp>

namespace {

class StaticListTest : public ::testing::Test {
protected:
  StaticListTest() {}
  virtual ~StaticListTest() { List::clear(); }

  using List = ztl::static_list<size_t>;
  using Node = ztl::node<size_t>;

  Node _node38{38};
  Node _node39{39};
  Node _node40{40};
  Node _node41{41};
  Node _node42{42};
  Node _node43{43};
  Node _node44{44};
  Node _node45{45};
  Node _node46{46};
};

} // namespace

TEST_F(StaticListTest, clear) {
  List::push_back(_node44);
  List::push_back(_node45);
  List::push_back(_node46);

  EXPECT_EQ(List::size(), 3uz);

  List::clear();

  EXPECT_EQ(List::size(), 0uz);
}

TEST_F(StaticListTest, empty) {
  EXPECT_TRUE(List::empty());
  List::push_back(_node38);
  EXPECT_FALSE(List::empty());
}

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
}

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

TEST_F(StaticListTest, push_front) {
  // 40 39 38
  List::push_front(_node38);
  List::push_front(_node39);
  List::push_front(_node40);

  auto it{List::begin()};
  EXPECT_EQ(*it++, 40);
  EXPECT_EQ(*it++, 39);
  EXPECT_EQ(*it, 38);

  EXPECT_EQ(List::front(), 40);
  EXPECT_EQ(List::back(), 38);

  EXPECT_EQ(List::size(), 3uz);
}

TEST_F(StaticListTest, size) {
  EXPECT_EQ(List::size(), 0uz);
  List::push_back(_node38);
  EXPECT_EQ(List::size(), 1uz);
  List::push_back(_node39);
  EXPECT_EQ(List::size(), 2uz);
  List::push_back(_node40);
  EXPECT_EQ(List::size(), 3uz);
}
