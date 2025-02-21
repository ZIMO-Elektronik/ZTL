#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/edge_detector.hpp>

TEST(edge_detector, ctor) {
  {
    ztl::edge_detector ed{false};
    EXPECT_EQ(ed(true), ztl::edge_detector::rising);
  }

  {
    ztl::edge_detector ed{true};
    EXPECT_EQ(ed(false), ztl::edge_detector::falling);
  }
}

TEST(edge_detector, function_call) {
  ztl::edge_detector ed;
  EXPECT_EQ(ed(false), ztl::edge_detector::none);
  EXPECT_EQ(ed(true), ztl::edge_detector::rising);
  EXPECT_EQ(ed(true), ztl::edge_detector::none);
  EXPECT_EQ(ed(false), ztl::edge_detector::falling);
  EXPECT_EQ(ed(false), ztl::edge_detector::none);
}