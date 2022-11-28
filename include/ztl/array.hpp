// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Array
///
/// \file   ztl/array.hpp
/// \author Vincent Hamp
/// \date   08/12/2016

#pragma once

#include <array>
#include <utility>

namespace ztl {

/// Make array with function and index sequence
///
/// \tparam T                           Type of array
/// \tparam F                           Type of callable object to be invoked
/// \param  U                           Type of range
/// \tparam Is...                       Indices
/// \param  f                           Callable object
/// \param  std::index_sequence<Is...>  Index sequence
/// \return Array
template<typename T, typename F, size_t... Is>
constexpr auto make_array(F&& f, std::index_sequence<Is...>) {
  return std::array<T, sizeof...(Is)>{
    {static_cast<T>(f(std::integral_constant<size_t, Is>{}))...}};
}

}  // namespace ztl
