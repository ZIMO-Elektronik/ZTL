#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/compilation_time.hpp>

TEST(compilation_time, compilation_time) {
  constexpr auto ct{ztl::make_compilation_time()};
  EXPECT_GE(ct.year, 2019);
}

TEST(compilation_time, unix_compilation_time) {
  constexpr auto ut{ztl::make_unix_compilation_time()};
  EXPECT_GT(ut, 1559555872);
}