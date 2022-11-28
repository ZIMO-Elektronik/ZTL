#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/meta.hpp>

// For each
TEST(meta, for_each) {
  using ::testing::Matcher;

  struct Functor {
    virtual ~Functor() {}
    virtual void f(int) = 0;
    virtual void f(char const*) = 0;
    virtual void f(char) = 0;
  };

  struct MockFunctor : Functor {
    MOCK_METHOD1(f, void(int));
    MOCK_METHOD1(f, void(char const*));
    MOCK_METHOD1(f, void(char));

    // Can't mock operator overloads directly
    void operator()(int i) { return f(i); }
    void operator()(char const* str) { return f(str); }
    void operator()(char c) { return f(c); }
  };

  MockFunctor mock_functor;
  auto t0{std::make_tuple(42, "aha!", 'c')};

  EXPECT_CALL(mock_functor, f(Matcher<int>(42))).Times(1);
  EXPECT_CALL(mock_functor, f("aha!")).Times(1);
  EXPECT_CALL(mock_functor, f(Matcher<char>('c'))).Times(1);

  ztl::for_each(t0, mock_functor);
}
