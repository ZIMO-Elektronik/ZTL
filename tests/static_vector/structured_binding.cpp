#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/static_vector.hpp>

TEST(static_vector, structured_binding) {
  ztl::static_vector<int, 42uz> c{0, 1, 2, 3, 4, 5};
}
