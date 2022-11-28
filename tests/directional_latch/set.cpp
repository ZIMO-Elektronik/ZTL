#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <optional>
#include <ztl/directional_latch.hpp>

TEST(directional_latch, set) {
  // Latching 4 times in the same direction yields new value
  {
    ztl::directional_latch<int, 4uz> dl{42};
    dl.set(43);  // 1
    dl.set(44);  // 2
    dl.set(43);  // 3
    dl.set(45);  // 4
    EXPECT_EQ(dl, 45);
  }

  {
    ztl::directional_latch<int, 4uz> dl{42};
    dl.set(39);  // 1
    dl.set(41);  // 2
    dl.set(40);  // 3
    dl.set(41);  // 4
    EXPECT_EQ(dl, 41);
  }

  // Latching in the other direction once resets internal counter
  {
    ztl::directional_latch<int, 4uz> dl{42};
    dl.set(43);  // 1
    dl.set(44);  // 2
    dl.set(41);  // 3
    dl.set(45);  // 4
    EXPECT_EQ(dl, 42);
  }

  // Latching the same value once resets internal counter
  {
    ztl::directional_latch<int, 4uz> dl{42};
    dl.set(43);  // 1
    dl.set(44);  // 2
    dl.set(42);  // 3
    dl.set(45);  // 4
    EXPECT_EQ(dl, 42);
  }
}
