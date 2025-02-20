#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/inplace_vector.hpp>

TEST(inplace_vector, ctor) {
  ztl::inplace_vector<int, 1uz> default_ctor;
  EXPECT_EQ(size(default_ctor), 0uz);

  ztl::inplace_vector<int, 5uz> variadic_ctor{1, 2, 3};
  EXPECT_EQ(variadic_ctor.front(), 1);
  EXPECT_EQ(variadic_ctor.back(), 3);
  EXPECT_EQ(size(variadic_ctor), 3uz);
  EXPECT_EQ(variadic_ctor.max_size(), 5uz);

  ztl::inplace_vector variadic_ctor_ctad{1, 2, 3};
  EXPECT_EQ(variadic_ctor_ctad.front(), 1);
  EXPECT_EQ(variadic_ctor_ctad.back(), 3);
  EXPECT_EQ(size(variadic_ctor_ctad), 3uz);
  EXPECT_EQ(variadic_ctor_ctad.max_size(), 3uz);
}

TEST(inplace_vector, empty) {
  ztl::inplace_vector<int, 3uz> c;
  EXPECT_TRUE(c.empty());

  c.push_back(5);
  EXPECT_FALSE(c.empty());

  c.pop_back();
  EXPECT_TRUE(c.empty());

  // Trying to remove further elements causes undefined behavior
  EXPECT_DEATH(c.pop_back(), "");
}

TEST(inplace_vector, full) {
  ztl::inplace_vector<int, 4uz> c;
  EXPECT_TRUE(c.empty());

  // Push till full
  c.push_back(0);
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  EXPECT_TRUE(c.full());

  // Removing one element
  c.pop_back();
  EXPECT_FALSE(c.full());

  // Adding one element
  c.push_back(4);
  EXPECT_EQ(c.back(), 4);
  EXPECT_TRUE(c.full());

  // Trying to add further elements causes undefined behavior
  EXPECT_DEATH(c.push_back(42), "");
}
