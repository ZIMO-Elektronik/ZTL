// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Delayed latch
///
/// \file   ztl/delayed_latch.hpp
/// \author Vincent Hamp
/// \date   20/02/2025

#pragma once

#include <chrono>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <utility>
#include "concepts.hpp"
#include "limits.hpp"

namespace ztl {

/// Latches T after it was set for at least I ticks
///
/// \tparam T         Type of latch
/// \tparam Duration  chrono_duration
template<std::equality_comparable T, chrono_duration Duration>
struct delayed_latch {
  using value_type = T;

  /// Default ctor
  constexpr delayed_latch() = default;

  /// Ctor
  ///
  /// \param  value     Initial value
  /// \param  duration  Duration
  constexpr delayed_latch(value_type const& value,
                          Duration const& duration = {})
    : _tp{std::chrono::system_clock::now()}, _value{value}, _next_value{value},
      _duration{duration} {}

  /// Set latch
  ///
  /// \param  value Next value
  void set(value_type const& value) {
    if (_next_value != value) {
      reset();
      _next_value = value;
    }
    if (std::chrono::system_clock::now() - _tp >= _duration)
      _value = _next_value;
  }

  /// Reset latch
  void reset() { _tp = std::chrono::system_clock::now(); }

  /// Reset latch
  ///
  /// \param  value Reset value
  void reset(value_type const& value) {
    reset();
    _value = _next_value = value;
  }

  /// Reset latch
  ///
  /// \param  duration  Reset duration
  void reset(Duration const& duration) {
    reset();
    _duration = duration;
  }

  constexpr value_type const& value() const& { return _value; }
  constexpr value_type const&& value() const&& { return std::move(_value); }

  constexpr operator value_type const&() const& { return value(); }
  constexpr operator value_type const&&() const&& { return std::move(value()); }

private:
  std::chrono::time_point<std::chrono::system_clock> _tp{};
  T _value{};
  T _next_value{};
  Duration _duration{};
};

} // namespace ztl
