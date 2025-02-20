#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ztl/type_traits.hpp>

namespace {

template<typename... Ts>
struct S : std::tuple<Ts...> {
  S() = default;
  S(Ts... ts) : std::tuple<Ts...>{ts...} {}
};

} // namespace

// Variadic version of std::is_same
TEST(type_traits, are_same) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::are_same_v<A, A, A>));
  EXPECT_FALSE((ztl::are_same_v<A, B>));
}

// Check if a template can have an empty argument list (e.g. std::tuple<>)
TEST(type_traits, can_have_empty_argument_list) {
  EXPECT_FALSE(ztl::can_have_empty_argument_list<std::vector>::value);
  EXPECT_TRUE(ztl::can_have_empty_argument_list_v<std::tuple>);
  EXPECT_TRUE(ztl::can_have_empty_argument_list_v<std::void_t>);
  EXPECT_FALSE(ztl::can_have_empty_argument_list<std::is_base_of>::value);
}

// Check if tuple contains a type
TEST(type_traits, contains_type) {
  auto t0{std::make_tuple(42, 42.42, "aha")};
  auto const t1{std::make_tuple("jup", 42)};
  auto& rt0{t0};

  struct S {};
  auto p0{std::make_pair(42, S{})};

  EXPECT_TRUE((ztl::contains_type<int, decltype(t0)>::value));
  EXPECT_TRUE((ztl::contains_type_v<int, decltype(t0)>));
  EXPECT_TRUE((ztl::contains_type_v<int, decltype(rt0)>));
  EXPECT_FALSE((ztl::contains_type<float, decltype(t1)>::value));
  EXPECT_FALSE((ztl::contains_type_v<float, decltype(t1)>));
  EXPECT_TRUE((ztl::contains_type_v<char const*, decltype(t1)>));
  EXPECT_TRUE((ztl::contains_type_v<S, decltype(p0)>));
}

// Check if more types are an integer sequence
TEST(type_traits, count_type) {
  EXPECT_EQ(1u, (ztl::count_type_v<int, double, char, int>));
  EXPECT_EQ(0u, (ztl::count_type_v<float, double, char, int>));
  EXPECT_EQ(2u, (ztl::count_type_v<int, double, int, int>));
  EXPECT_EQ(3u, (ztl::count_type_v<int, int, int, int>));
  EXPECT_NE(4u, (ztl::count_type_v<int, int, int, int>));
}

// Check if a type has all bases from some other types
TEST(type_traits, has_base_from_all) {
  struct B0 {};
  struct B1 {};
  struct D1 : B0 {};
  struct D2 : B0, B1 {};

  B0 b0;
  auto& rb0{b0};

  D1 d1;
  auto& rd1{d1};

  EXPECT_TRUE((ztl::has_base_from_all<D1, B0>::value));
  EXPECT_TRUE((ztl::has_base_from_all<D1, decltype(b0)>::value));
  EXPECT_TRUE((ztl::has_base_from_all<D1, decltype(rb0)>::value));
  EXPECT_TRUE((ztl::has_base_from_all_v<decltype(d1), B0>));
  EXPECT_TRUE((ztl::has_base_from_all_v<decltype(rd1), B0>));
  EXPECT_FALSE((ztl::has_base_from_all_v<D1, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_all<B0, B0>::value));
  EXPECT_FALSE((ztl::has_base_from_all<D1, B1>::value));
  EXPECT_TRUE((ztl::has_base_from_all_v<D2, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_all<D2, B0>::value));
}

// Check if a type has any base from some other types (basically variadic
// version of is_base the other way round)
TEST(type_traits, has_base_from_any) {
  struct B0 {};
  struct B1 {};
  struct D1 : B0 {};
  struct D2 : B1 {};

  B0 b0;
  auto& rb0{b0};

  D2 d2;
  auto& rd2{d2};

  EXPECT_TRUE((ztl::has_base_from_any<D1, B0>::value));
  EXPECT_TRUE((ztl::has_base_from_any_v<D1, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_any_v<D1, decltype(rb0), B1>));
  EXPECT_TRUE((ztl::has_base_from_any<B0, B0>::value));
  EXPECT_FALSE((ztl::has_base_from_any<D1, B1>::value));
  EXPECT_TRUE((ztl::has_base_from_any_v<D2, B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_any_v<decltype(d2), B0, B1>));
  EXPECT_TRUE((ztl::has_base_from_any_v<decltype(rd2), B0, B1>));
  EXPECT_FALSE((ztl::has_base_from_any<D2, B0>::value));
}

// Check if a type is derived from all other types
TEST(type_traits, is_derived_from_all) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::is_derived_from_all_v<H, C, D, E>));
  EXPECT_FALSE((ztl::is_derived_from_all_v<H, C, D, E, G>));
  EXPECT_TRUE((ztl::is_derived_from_all_v<F, B>));
  EXPECT_TRUE((ztl::is_derived_from_all_v<G, C>));
  EXPECT_TRUE((ztl::is_derived_from_all_v<G, C, E>));
  EXPECT_FALSE((ztl::is_derived_from_all_v<G, C, E, H>));
}

// Check if a type is derived from any other types
TEST(type_traits, is_derived_from_any) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::is_derived_from_any_v<H, C>));
  EXPECT_TRUE((ztl::is_derived_from_any_v<H, C, A>));
  EXPECT_FALSE((ztl::is_derived_from_any_v<A, B, C, D, E>));
}

// Check if a type is derived from some base
TEST(type_traits, is_derived_from) {
  struct A {};
  struct B {};
  struct C {};
  struct D {};
  struct E {};
  struct F : B {};
  struct G : C, E {};
  struct H : C, D, E {};

  EXPECT_TRUE((ztl::is_derived_from<H, C>::value));
  EXPECT_FALSE((ztl::is_derived_from_v<H, G>));
  EXPECT_TRUE((ztl::is_derived_from_v<F, B>));
  EXPECT_TRUE((ztl::is_derived_from<G, C>::value));
  EXPECT_TRUE((ztl::is_derived_from<G, E>::value));
  EXPECT_FALSE((ztl::is_derived_from_v<G, A>));
}

// Check if a type is a specialization of a template
TEST(type_traits, is_specialization_of) {
  auto t0{std::make_tuple(42)};
  auto const t1{std::make_tuple(42)};
  std::vector<int> volatile v0{42};

  EXPECT_TRUE((ztl::is_specialization_of_v<decltype(t0), std::tuple>));
  EXPECT_TRUE((ztl::is_specialization_of_v<decltype(t1), std::tuple>));
  EXPECT_TRUE(
    (ztl::is_specialization_of_v<decltype(t0), std::tuple, std::pair>));
  EXPECT_FALSE((ztl::is_specialization_of_v<decltype(t0), std::pair>));
  EXPECT_TRUE((ztl::is_specialization_of_v<decltype(v0), std::vector>));
}

// Check if a type is a template
TEST(type_traits, is_template) {
  std::tuple<int> t;
  std::vector<char> v;
  std::basic_string<char> s;
  auto l{[] {}};

  EXPECT_TRUE(ztl::is_template_v<decltype(t)>);
  EXPECT_TRUE(ztl::is_template_v<decltype(v)>);
  EXPECT_TRUE(ztl::is_template_v<decltype(s)>);
  EXPECT_FALSE(ztl::is_template_v<int>);
  EXPECT_FALSE(ztl::is_template_v<decltype(l)>);
}

// Get size of arbitrary sequence type
TEST(type_traits, template_size) {
  auto t0{std::make_tuple(1, 2, 3, 4, 5)};
  S s0{1337, 42.42, "hello world"};
  auto p0{std::make_pair(42, 43)};

  EXPECT_EQ(5, (ztl::template_size_v<decltype(t0)>));
  EXPECT_EQ(3, (ztl::template_size_v<decltype(s0)>));
  EXPECT_EQ(2, (ztl::template_size_v<decltype(p0)>));
}

// Use template type to create new type
TEST(type_traits, template_t) {
  S s0{42, 43, "wtf"};
  ztl::template_t<decltype(s0), char, float> s1{};
  auto t0{std::make_tuple('c', 42)};
  ztl::template_t<decltype(t0), char, char> t1{};

  EXPECT_TRUE((std::same_as<S<char, float>, decltype(s1)>));
  EXPECT_TRUE((std::same_as<std::tuple<char, char>, decltype(t1)>));
}

// Get index of type in tuple
TEST(type_traits, tuple_index) {
  using Tuple = std::tuple<int, double, char>;

  auto i0{ztl::tuple_index_v<int, Tuple>};
  EXPECT_EQ(i0, 0u);

  auto i1{ztl::tuple_index_v<double, Tuple>};
  EXPECT_EQ(i1, 1u);

  auto i2{ztl::tuple_index_v<char, Tuple>};
  EXPECT_EQ(i2, 2u);

  // fails with static_assertion
  // auto i3{ztl::tuple_index_v<std::string, Tuple>};
  // EXPECT_EQ(i3, 0u);
}

// Get index of type in typelist
TEST(type_traits, type_index) {
  auto i0 = ztl::type_index<int, double, char, int>{};
  EXPECT_EQ(2u, i0);

  auto i1 = ztl::type_index<float&, double, char, int, float&, int>{};
  EXPECT_EQ(3u, i1);

  auto i2 = ztl::type_index<int, double, int, char>{};
  EXPECT_EQ(1u, i2);

  // fails with static_assertion
  //  auto i = ztl::type_index<int, double, char, float>{};
  //  EXPECT_EQ(0, i);
}
