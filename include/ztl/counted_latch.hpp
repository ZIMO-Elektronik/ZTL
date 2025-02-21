// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Counted latch
///
/// \file   ztl/counted_latch.hpp
/// \author Vincent Hamp
/// \date   05/09/2018

#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <utility>
#include "limits.hpp"

namespace ztl {

/// Latches T after it was set for at least I times
///
/// \tparam T Type of latch
/// \tparam I Times to latch
template<std::equality_comparable T, size_t I>
requires(I > 0uz)
struct counted_latch {
  using value_type = T;

  /// Default ctor
  constexpr counted_latch() = default;

  /// Ctor
  ///
  /// \param  value Initial value
  constexpr counted_latch(value_type const& value)
    : _value{value}, _next_value{value} {}

  /// Set latch
  ///
  /// \param  value Next value
  void set(value_type const& value) {
    if (_next_value != value) {
      reset();
      _next_value = value;
    }
    if (++_count < I) return;
    _value = _next_value;
  }

  /// Reset latch
  void reset() { _count = 0u; }

  /// Reset latch
  ///
  /// \param  value Reset value
  void reset(value_type const& value) {
    reset();
    _value = _next_value = value;
  }

  constexpr value_type const& value() const& { return _value; }
  constexpr value_type const&& value() const&& { return std::move(_value); }

  constexpr operator value_type const&() const& { return value(); }
  constexpr operator value_type const&&() const&& { return std::move(value()); }

private:
  T _value{};
  T _next_value{};
  smallest_unsigned_t<I> _count{};
};

} // namespace ztl
