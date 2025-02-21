// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Moving average
///
/// \file   ztl/moving_average.hpp
/// \author Vincent Hamp
/// \date   04/12/2018

#pragma once

#include <cstdint>

namespace ztl {

/// Moving average
///
/// The boolean template parameter Precision can be used to choose between two
/// ways the average is calculated. The more precise variant needs to store T *
/// window size instead of just T. This allows the addition assignment to take
/// smaller values into account which would otherwise get rounded to zero.
///
/// \tparam T         Type
/// \tparam I         Averaging window size
/// \tparam Precision true  More precise but needs to store T * window size
///                   false May lose precision when using small values
template<typename T, int I, bool Precision = true>
struct moving_average {
  static_assert(I > 1);

  using value_type = T;

  /// Default ctor
  constexpr moving_average() = default;

  /// Ctor
  constexpr moving_average(value_type const& rhs)
    : _value{Precision ? static_cast<value_type>(rhs * I) : rhs} {}

  /// Assignment
  value_type& operator=(value_type const& rhs) {
    return _value = Precision ? static_cast<value_type>(rhs * I) : rhs;
  }

  /// Addition assignment
  value_type& operator+=(value_type const& rhs) {
    if constexpr (Precision)
      return _value = static_cast<value_type>(_value + (rhs - _value / I));
    else return _value = static_cast<value_type>(_value + (rhs - _value) / I);
  }

  constexpr value_type value() const {
    if constexpr (Precision) return static_cast<value_type>(_value / I);
    else return _value;
  }

  constexpr operator value_type() const { return value(); }

private:
  value_type _value{};
};

} // namespace ztl
