#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/compilation_time.hpp>

TEST(compilation_time, compilation_time) {
  constexpr auto ct{ztl::make_compilation_time()};
  EXPECT_GE(ct.year, 2019);
}