#pragma once

#include <gtest/gtest.h>
#include <ztl/static_list.hpp>

// static_list test fixture
class StaticListTest : public ::testing::Test {
public:
  StaticListTest();
  virtual ~StaticListTest();

protected:
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
