// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Type traits
///
/// \file   ztl/type_traits.hpp
/// \author Vincent Hamp
/// \date   08/12/2016

#pragma once

#include <array>
#include <concepts>
#include "utility.hpp"

namespace ztl {

/// Check if all Ts... are T
///
/// \tparam T     Type to look for
/// \tparam Ts... Types to compare against
template<typename T, typename... Ts>
using are_same = std::conjunction<std::is_same<T, Ts>...>;

template<typename T, typename... Ts>
inline constexpr bool are_same_v{are_same<T, Ts...>::value};

namespace detail {

template<auto... Is>
struct count_type_impl
  : std::integral_constant<decltype((Is, ...)), (Is + ... + 0u)> {};

} // namespace detail

/// Count occurrences of T in Ts...
///
/// \tparam T     Type to count
/// \tparam Ts... Types to count in
template<typename T, typename... Ts>
using count_type = detail::count_type_impl<(std::same_as<T, Ts> ? 1u : 0u)...>;

template<typename T, typename... Ts>
inline constexpr size_t count_type_v{count_type<T, Ts...>::value};

namespace detail {

template<template<typename...> typename, typename = void>
struct can_have_empty_argument_list_impl : std::false_type {};

template<template<typename...> typename T>
struct can_have_empty_argument_list_impl<T, std::void_t<T<>>> : std::true_type {
};

} // namespace detail

/// Check if template T can have an empty template argument list
///
/// \tparam T Template to check
template<template<typename...> typename T>
using can_have_empty_argument_list =
  detail::can_have_empty_argument_list_impl<T>;

template<template<typename...> typename T>
inline constexpr bool can_have_empty_argument_list_v{
  can_have_empty_argument_list<T>::value};

namespace detail {

template<typename>
struct is_template_impl : std::false_type {};

template<template<typename...> typename T, typename... Ts>
struct is_template_impl<T<Ts...>> : std::true_type {};

} // namespace detail

/// Check if T is a template
///
/// \tparam T Type to check
template<typename T>
using is_template = detail::is_template_impl<std::remove_cvref_t<T>>;

template<typename T>
inline constexpr bool is_template_v{is_template<T>::value};

namespace detail {

template<typename T, typename U>
struct is_derived_from_impl {
  using type =
    std::conditional_t<std::is_base_of_v<U, T> && !std::same_as<U, T>,
                       std::true_type,
                       std::false_type>;
};

} // namespace detail

/// Check if T derives from U
///
/// \tparam T Derived
/// \tparam U Base
template<typename T, typename U>
using is_derived_from =
  typename detail::is_derived_from_impl<std::remove_cvref_t<T>,
                                        std::remove_cvref_t<U>>::type;

template<typename T, typename U>
inline constexpr bool is_derived_from_v{is_derived_from<T, U>::value};

/// Check if T derives from all Ts...
///
/// \tparam T     Derived
/// \tparam Ts... Bases
template<typename T, typename... Ts>
using is_derived_from_all = std::conjunction<is_derived_from<T, Ts>...>;

template<typename T, typename... Ts>
inline constexpr bool is_derived_from_all_v{
  is_derived_from_all<T, Ts...>::value};

/// Check if T derives from any Ts...
///
/// \tparam T     Derived
/// \tparam Ts... Bases
template<typename T, typename... Ts>
using is_derived_from_any = std::disjunction<is_derived_from<T, Ts>...>;

template<typename T, typename... Ts>
inline constexpr bool is_derived_from_any_v{
  is_derived_from_any<T, Ts...>::value};

namespace detail {

template<typename, template<typename...> typename>
struct is_specialization_of_impl : std::false_type {};

template<template<typename...> typename T, typename... Ts>
struct is_specialization_of_impl<T<Ts...>, T> : std::true_type {};

} // namespace detail

/// Check if T is any specialized type of Ts...
///
/// \tparam T     Specialized type
/// \tparam Ts... Types to specialize from
template<typename T, template<typename...> typename... Ts>
using is_specialization_of = std::disjunction<
  detail::is_specialization_of_impl<std::remove_cvref_t<T>, Ts>...>;

template<typename T, template<typename...> typename... Ts>
inline constexpr bool is_specialization_of_v{
  is_specialization_of<T, Ts...>::value};

namespace detail {

template<typename, typename>
struct contains_type_impl : std::false_type {};

template<typename T, template<typename...> typename U, typename... Us>
struct contains_type_impl<T, U<Us...>>
  : std::disjunction<std::is_same<T, Us>...> {};

} // namespace detail

/// Check if any type in U is T
///
/// \tparam T Type to look for
/// \tparam U Type to look in
template<typename T, typename U>
using contains_type = detail::contains_type_impl<T, std::remove_cvref_t<U>>;

template<typename T, typename U>
inline constexpr bool contains_type_v{contains_type<T, U>::value};

/// Check if T has or is all bases in Ts...
///
/// \tparam T     Derived
/// \tparam Ts... Bases
template<typename T, typename... Ts>
using has_base_from_all = std::conjunction<
  std::is_base_of<std::remove_cvref_t<Ts>, std::remove_cvref_t<T>>...>;

template<typename T, typename... Ts>
inline constexpr bool has_base_from_all_v{has_base_from_all<T, Ts...>::value};

/// Check if T has or is any base in Ts...
///
/// \tparam T     Derived
/// \tparam Ts... Bases
template<typename T, typename... Ts>
using has_base_from_any = std::disjunction<
  std::is_base_of<std::remove_cvref_t<Ts>, std::remove_cvref_t<T>>...>;

template<typename T, typename... Ts>
inline constexpr bool has_base_from_any_v{has_base_from_any<T, Ts...>::value};

namespace detail {

template<typename...>
struct type_index_impl;

template<size_t... Is, typename T, typename... Ts>
struct type_index_impl<std::index_sequence<Is...>, T, Ts...>
  : detail::count_type_impl<(std::same_as<T, Ts> ? Is : 0u)...> {
  static_assert(count_type_v<T, Ts...> == 1u);
};

} // namespace detail

/// Get index of T in Ts...
///
/// \tparam T     Type to get index for
/// \tparam Ts... Types to look in
template<typename T, typename... Ts>
using type_index =
  detail::type_index_impl<std::index_sequence_for<Ts...>, T, Ts...>;

template<typename T, typename... Ts>
inline constexpr size_t type_index_v{type_index<T, Ts...>::value};

/// Get index of T in tuple U
///
/// \tparam T Type to get index for
/// \tparam U Tuple to look in
template<typename T, typename U>
struct tuple_index {
  static constexpr size_t value{std::invoke(
    []<size_t... Is>(std::index_sequence<Is...>) {
      static_assert(count_type_v<T, std::tuple_element_t<Is, U>...> == 1u);
      return ((std::same_as<T, std::tuple_element_t<Is, U>> ? Is : 0u) + ...);
    },
    std::make_index_sequence<std::tuple_size_v<U>>{})};
};

template<typename T, typename U>
inline constexpr size_t tuple_index_v{tuple_index<T, U>::value};

namespace detail {

template<typename>
struct template_size_impl;

template<template<typename...> typename T, typename... Ts>
struct template_size_impl<T<Ts...>> {
  static constexpr size_t value{sizeof...(Ts)};
};

} // namespace detail

/// Provide access to number of elements in a template
///
/// \tparam T Template
template<typename T>
using template_size = detail::template_size_impl<std::remove_cvref_t<T>>;

template<typename T>
inline constexpr size_t template_size_v{template_size<T>::value};

namespace detail {

template<typename, typename...>
struct template_impl;

template<template<typename...> typename T, typename... Ts, typename... Us>
struct template_impl<T<Ts...>, Us...> {
  using type = T<Us...>;
};

} // namespace detail

/// Use template type T with template arguments Ts...
///
/// \tparam T     Template type
/// \tparam Ts... Template arguments
template<typename T, typename... Ts>
using template_t =
  typename detail::template_impl<std::remove_cvref_t<T>, Ts...>::type;

namespace detail {

template<typename>
struct is_chrono_duration : std::false_type {};

template<typename Rep, typename Period>
struct is_chrono_duration<std::chrono::duration<Rep, Period>> : std::true_type {
};

} // namespace detail

/// Check if T is a chrono_duration
///
/// \tparam T Type to check
template<typename T>
using is_chrono_duration = detail::is_chrono_duration<std::remove_cvref_t<T>>;

template<typename T>
inline constexpr bool is_chrono_duration_v{is_chrono_duration<T>::value};

} // namespace ztl
