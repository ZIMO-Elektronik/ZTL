// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Fixed string
///
/// \file   ztl/fixed_string.hpp
/// \author Vincent Hamp
/// \date   28/11/2022

#pragma once

#include <algorithm>
#include <utility>

namespace ztl {

/// Fixed string
///
/// \tparam I String length
template<size_t I>
struct fixed_string {
  constexpr fixed_string() {}

  constexpr fixed_string(char const (&str)[I + 1uz]) {
    std::copy_n(&str[0uz], I, begin(str_));
  }

  constexpr char const* c_str() const { return data(str_); }

  constexpr auto operator[](size_t i) const { return str_[i]; };

  std::array<char, I + 1uz> str_{};
};

template<size_t I>
fixed_string(char const (&)[I]) -> fixed_string<I - 1uz>;

template<fixed_string Fs>
constexpr auto operator""_fs() {
  return Fs;
}

template<size_t I, size_t J>
constexpr auto operator+(fixed_string<I> const& lhs,
                         fixed_string<J> const& rhs) {
  return [&]<size_t... Is, size_t... Js>(std::index_sequence<Is...>,
                                         std::index_sequence<Js...>) {
    return fixed_string{{lhs[Is]..., rhs[Js]...}};
  }
  (std::make_index_sequence<I>{}, std::make_index_sequence<J + 1uz>{});
}

}  // namespace ztl
