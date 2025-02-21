#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/concepts.hpp>

// Check if type is chrono_duration
TEST(concepts, chrono_duration) {
  std::chrono::milliseconds ms{10};
  auto i{42};
  std::chrono::seconds s{10};
  std::chrono::hours const h{3};

  EXPECT_TRUE(ztl::chrono_duration<decltype(ms)>);
  EXPECT_FALSE(ztl::chrono_duration<decltype(i)>);
  EXPECT_FALSE(ztl::chrono_duration<std::nullopt_t>);
  EXPECT_TRUE(ztl::chrono_duration<decltype(s)>);
  EXPECT_TRUE(ztl::chrono_duration<decltype(h)>);
}
