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

  Node node38{38};
  Node node39{39};
  Node node40{40};
  Node node41{41};
  Node node42{42};
  Node node43{43};
  Node node44{44};
  Node node45{45};
  Node node46{46};
};
