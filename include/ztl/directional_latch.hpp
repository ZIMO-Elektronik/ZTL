// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Directional latch
///
/// \file   ztl/directional_latch.hpp
/// \author Vincent Hamp
/// \date   25/03/2021

#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <utility>
#include "limits.hpp"

namespace ztl {

/// Latches T after it hasn't changed direction for at least I times
///
/// \tparam T Type of latch
/// \tparam I Times to latch
template<std::totally_ordered T, size_t I>
struct directional_latch {
  using value_type = T;

  /// Default ctor
  constexpr directional_latch() = default;

  /// Ctor
  ///
  /// \param  value Initial value
  constexpr directional_latch(value_type const& value) : _value{value} {};

  /// Set latch
  ///
  /// \param  value Next value
  void set(value_type const& value) {
    if ((value == _value) || (_less && value > _value) ||
        (!_less && value < _value))
      reset();
    if (!_count) _less = value < _value;
    if (++_count < I) return;
    reset();
    _value = value;
  }

  /// Reset latch
  void reset() { _count = 0u; }

  /// Reset latch
  ///
  /// \param  value Reset value
  void reset(value_type const& value) {
    reset();
    _value = value;
  }

  constexpr value_type const& value() const& { return _value; }
  constexpr value_type const&& value() const&& { return std::move(_value); }

  constexpr operator value_type const&() const& { return value(); }
  constexpr operator value_type const&&() const&& { return std::move(value()); }

private:
  T _value{};
  smallest_unsigned_t<I> _count{};
  bool _less{};
};

}  // namespace ztl
