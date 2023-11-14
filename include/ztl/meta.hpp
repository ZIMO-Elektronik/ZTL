// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Meta
///
/// \file   ztl/meta.hpp
/// \author Vincent Hamp
/// \date   27/04/2017

#pragma once

#include <cassert>
#include "type_traits.hpp"
#include "utility.hpp"

namespace ztl {

namespace detail {

template<typename T, typename F, size_t... Is>
constexpr void for_each_impl(T&& t, F&& f, std::index_sequence<Is...>) {
  (f(get<Is>(std::forward<T>(t))), ...);
}

}  // namespace detail

/// Applies a callable object to each sequence element
///
/// \tparam T Type of sequence
/// \tparam F Type of callable object to be invoked
/// \param  t Sequence
/// \param  f Callable object
template<typename T, typename F>
constexpr void for_each(T&& t, F&& f) {
  detail::for_each_impl(
    std::forward<T>(t),
    std::forward<F>(f),
    std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>{});
}

namespace detail {

/// Reverse the order of the elements implementation
///
/// \tparam T                           Type of sequence
/// \tparam Is...                       Indices
/// \param  t                           Sequence
/// \param  std::index_sequence<Is...>  Index sequence
/// \return Reversed sequence
template<typename T, size_t... Is>
constexpr auto reverse_impl(T&& t, std::index_sequence<Is...>) {
  return template_t<T, std::tuple_element_t<Is, std::remove_cvref_t<T>>...>{
    get<Is>(std::forward<T>(t))...};
}

}  // namespace detail

/// Reverse the order of the elements
///
/// \tparam T Type of sequence
/// \param  t Sequence
/// \return Reversed sequence
template<typename T>
constexpr auto reverse(T&& t) {
  return detail::reverse_impl(
    std::forward<T>(t),
    make_reverse_index_sequence<std::tuple_size_v<std::remove_cvref_t<T>>>{});
}

}  // namespace ztl
