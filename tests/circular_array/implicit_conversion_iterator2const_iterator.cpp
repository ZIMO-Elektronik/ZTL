#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/circular_array.hpp>

// const_iterator can be constructed and assigned from iterator
TEST(circular_array, implicit_conversion_iterator2const_iterator) {
  ztl::circular_array<int, 1uz>::iterator iterator;
  ztl::circular_array<int, 1uz>::const_iterator const_iterator{iterator};
  const_iterator = iterator;
}
