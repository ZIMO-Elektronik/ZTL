#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/edge_detector.hpp>

TEST(edge_detector, ctor) {
  {
    ztl::EdgeDetector edge_detector{false};
    EXPECT_EQ(edge_detector(true), ztl::EdgeDetector::Rising);
  }

  {
    ztl::EdgeDetector edge_detector{true};
    EXPECT_EQ(edge_detector(false), ztl::EdgeDetector::Falling);
  }
}

TEST(edge_detector, function_call) {
  ztl::EdgeDetector edge_detector;
  EXPECT_EQ(edge_detector(false), ztl::EdgeDetector::None);
  EXPECT_EQ(edge_detector(true), ztl::EdgeDetector::Rising);
  EXPECT_EQ(edge_detector(true), ztl::EdgeDetector::None);
  EXPECT_EQ(edge_detector(false), ztl::EdgeDetector::Falling);
  EXPECT_EQ(edge_detector(false), ztl::EdgeDetector::None);
}