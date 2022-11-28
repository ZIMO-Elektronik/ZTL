#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "e.hpp"

TEST(enum, unary_minus) {
  EXPECT_EQ(-E::B, -2);
  EXPECT_EQ(-E::E, 42);
}
