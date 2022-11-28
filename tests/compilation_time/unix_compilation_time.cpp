#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/compilation_time.hpp>

TEST(compilation_time, unix_compilation_time) {
  constexpr auto ut{ztl::make_unix_compilation_time()};
  EXPECT_GT(ut, 1559555872);
}