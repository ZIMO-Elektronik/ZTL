#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/static_vector.hpp>

TEST(static_vector, ctor) {
  ztl::static_vector<int, 1uz> default_ctor;
  EXPECT_EQ(size(default_ctor), 0uz);

  ztl::static_vector<int, 5uz> variadic_ctor{1, 2, 3};
  EXPECT_EQ(variadic_ctor.front(), 1);
  EXPECT_EQ(variadic_ctor.back(), 3);
  EXPECT_EQ(size(variadic_ctor), 3uz);
  EXPECT_EQ(variadic_ctor.max_size(), 5uz);

  ztl::static_vector variadic_ctor_ctad{1, 2, 3};
  EXPECT_EQ(variadic_ctor_ctad.front(), 1);
  EXPECT_EQ(variadic_ctor_ctad.back(), 3);
  EXPECT_EQ(size(variadic_ctor_ctad), 3uz);
  EXPECT_EQ(variadic_ctor_ctad.max_size(), 3uz);
}
