#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/explicit_wrapper.hpp>
#include <ztl/moving_average.hpp>

TEST(moving_average, moving_average) {
  {
    auto avg{ztl::moving_average<int16_t, 8, false>{}};

    avg += 100;
    EXPECT_EQ(avg, 12);

    avg += 100;
    EXPECT_EQ(avg, 23);

    avg += 100;
    EXPECT_EQ(avg, 32);

    avg += 100;
    EXPECT_EQ(avg, 40);

    avg += 100;
    EXPECT_EQ(avg, 47);

    avg += 100;
    EXPECT_EQ(avg, 53);

    avg += 100;
    EXPECT_EQ(avg, 58);

    for (auto i{0u}; i < 10; ++i)
      avg += 100;

    EXPECT_EQ(avg, 86);
  }

  {
    auto avg{ztl::moving_average<int16_t, 8, true>{}};

    avg += 100;
    EXPECT_EQ(avg, 12);

    avg += 100;
    EXPECT_EQ(avg, 23);

    avg += 100;
    EXPECT_EQ(avg, 33);

    avg += 100;
    EXPECT_EQ(avg, 41);

    avg += 100;
    EXPECT_EQ(avg, 48);

    avg += 100;
    EXPECT_EQ(avg, 55);

    avg += 100;
    EXPECT_EQ(avg, 61);

    for (auto i{0u}; i < 10; ++i)
      avg += 100;

    EXPECT_EQ(avg, 90);
  }
}