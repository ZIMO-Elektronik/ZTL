// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Utility header
///
/// \file   ztl/utility.hpp
/// \author Vincent Hamp
/// \date   12/11/2016

#pragma once

#include <array>
#include <functional>
#include "bits.hpp"

// Make std::integer_sequence tuple-like accessible
namespace std {

template<typename T, T... Is>
struct tuple_size<integer_sequence<T, Is...>>
  : integral_constant<size_t, sizeof...(Is)> {};

template<size_t I, typename T, T... Is>
struct tuple_element<I, integer_sequence<T, Is...>> {
  using type = tuple_element_t<I, tuple<integral_constant<T, Is>...>>;
};

}  // namespace std

namespace ztl {

/// Overload addition
///
/// \tparam T Type of lhs integral constant
/// \tparam I Constant of lhs integral constant
/// \tparam U Type of rhs integral constant
/// \tparam J Constant of rhs integral constant
/// \return Integral constant of common type
template<typename T, T I, typename U, U J>
constexpr auto operator+(std::integral_constant<T, I>,
                         std::integral_constant<U, J>) {
  return std::integral_constant<std::common_type_t<T, U>, I + J>{};
}

/// Overload subtraction
///
/// \tparam T Type of lhs integral constant
/// \tparam I Constant of lhs integral constant
/// \tparam U Type of rhs integral constant
/// \tparam J Constant of rhs integral constant
/// \return Integral constant of common type
template<typename T, T I, typename U, U J>
constexpr auto operator-(std::integral_constant<T, I>,
                         std::integral_constant<U, J>) {
  return std::integral_constant<std::common_type_t<T, U>, I - J>{};
}

/// Overload multiplication
///
/// \tparam T Type of lhs integral constant
/// \tparam I Constant of lhs integral constant
/// \tparam U Type of rhs integral constant
/// \tparam J Constant of rhs integral constant
/// \return Integral constant of common type
template<typename T, T I, typename U, U J>
constexpr auto operator*(std::integral_constant<T, I>,
                         std::integral_constant<U, J>) {
  return std::integral_constant<std::common_type_t<T, U>, I * J>{};
}

/// Overload division
///
/// \tparam T Type of lhs integral constant
/// \tparam I Constant of lhs integral constant
/// \tparam U Type of rhs integral constant
/// \tparam J Constant of rhs integral constant
/// \return Integral constant of common type
template<typename T, T I, typename U, U J>
constexpr auto operator/(std::integral_constant<T, I>,
                         std::integral_constant<U, J>) {
  return std::integral_constant<std::common_type_t<T, U>, I / J>{};
}

/// Extracts the Ith element from an integer sequence
///
/// \tparam I                               Element to access
/// \tparam T                               Type of integer sequence
/// \tparam Is...                           Integers
/// \param  std::integer_sequence<T, Is...> Integer sequence
/// \return Selected element of integer sequence
template<size_t I, typename T, T... Is>
constexpr auto get(std::integer_sequence<T, Is...>) {
  static_assert(I < sizeof...(Is));
  return std::tuple_element_t<I, std::integer_sequence<T, Is...>>{};
}

namespace detail {

template<typename T, T... Is, size_t... Js>
constexpr auto reverse_impl(std::integer_sequence<T, Is...>,
                            std::index_sequence<Js...>) {
  return std::integer_sequence<T,
                               get<sizeof...(Js) - Js - 1u>(
                                 std::index_sequence<Is...>{})...>{};
}

}  // namespace detail

/// Reverse integer sequence
///
/// \tparam T                               Type of integer sequence
/// \tparam Is...                           Integers
/// \param  std::integer_sequence<T, Is...> Integer sequence
/// \return Reversed std::integer_sequence<T, Is...>
template<typename T, T... Is>
constexpr auto reverse(std::integer_sequence<T, Is...>) {
  return detail::reverse_impl(std::integer_sequence<T, Is...>{},
                              std::make_index_sequence<sizeof...(Is)>{});
}

/// Make reverse integer sequence
///
/// \tparam T Type of integer sequence
/// \tparam I From
/// \tparam J To
/// \return Reverse std::integer_sequence<T, Is...>
template<typename T, T I>
using make_reverse_integer_sequence =
  decltype(reverse(std::make_integer_sequence<T, I>{}));

/// Make reverse index sequence
///
/// \tparam I From
/// \tparam J To
/// \return Reverse std::index_sequence<Is...>
template<size_t I>
using make_reverse_index_sequence = make_reverse_integer_sequence<size_t, I>;

namespace detail {

template<typename T, T I, T... Is>
auto make_integer_sequence_from_to_impl(std::integer_sequence<T, Is...>) {
  return std::integer_sequence<T, I + Is...>{};
}

template<typename T, T I, T J>
auto make_integer_sequence_from_to_impl() {
  if constexpr (I < J)
    return make_integer_sequence_from_to_impl<T, I>(
      std::make_integer_sequence<T, (I < J ? J - I : I - J)>{});
  else
    return make_integer_sequence_from_to_impl<T, J + 1>(
      make_reverse_integer_sequence<T, (I < J ? J - I : I - J)>{});
}

}  // namespace detail

/// Make integer sequence in half-open interval [From, To)
///
/// \tparam T Type of integer sequence
/// \tparam I From
/// \tparam J To
/// \return std::integer_sequence<T, Is...> from half-open interval [From, To)
template<typename T, T I, T J>
using make_integer_sequence_from_to =
  decltype(detail::make_integer_sequence_from_to_impl<T, I, J>());

/// Make index sequence in half-open interval [From, To)
///
/// \tparam I From
/// \tparam J To
/// \return std::index_sequence<Is...> from half-open interval [From, To)
template<size_t I, size_t J>
using make_index_sequence_from_to = make_integer_sequence_from_to<size_t, I, J>;

/// Index sequence to mask (TODO should be consteval, can't be because of bug)
///
/// \tparam Is...                     Indices
/// \param  std::index_sequenc<Is...> Index sequence
/// \return Mask
template<size_t... Is>
constexpr uint32_t index_sequence2mask(std::index_sequence<Is...>) {
  if constexpr (!sizeof...(Is)) return 0u;
  else return ((1u << Is) | ...);
}

}  // namespace ztl
