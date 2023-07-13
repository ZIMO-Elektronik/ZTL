#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_deque.hpp>

// const_iterator can be constructed and assigned from iterator
TEST(inplace_deque, implicit_conversion_iterator2const_iterator) {
  ztl::inplace_deque<int, 1uz>::iterator iterator;
  ztl::inplace_deque<int, 1uz>::const_iterator const_iterator{iterator};
  const_iterator = iterator;
}
