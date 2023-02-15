// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Constexpr math
///
/// \file   ztl/math.hpp
/// \author Vincent Hamp
/// \date   12/12/2016

#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>

namespace ztl {

/// Align value to alignment
///
/// \param  alignment Alignment
/// \param  value     Value to align
/// \return Aligned value
constexpr size_t align(size_t alignment, size_t value) {
  return value + (alignment - value % alignment) % alignment;
}

/// Log2 floor
///
/// \param  value Value
/// \return floor(log2(n))
constexpr uint32_t floor_log2(uint32_t value) {
  return value == 1u ? 0u : 1u + floor_log2(value >> 1u);
}

/// Log2 ceil
///
/// \param  value Value
/// \return ceil(log2(n))
constexpr uint32_t ceil_log2(uint32_t value) {
  return value == 1u ? 0u : floor_log2(value - 1u) + 1u;
}

/// Linear interpolation
///
/// \tparam T   Type of value
/// \param  x   Value
/// \param  x1  Part of interval(x1, x2)
/// \param  x2  Part of interval(x1, x2)
/// \param  y1  Part of interval(y1, y2)
/// \param  y2  Part of interval(y1, y2)
/// \return Interpolated value
template<typename T>
constexpr T lerp(T x, T x1, T x2, T y1, T y2) {
  if (x1 == x2) return y1;
  else return y1 + ((y2 - y1) * (x - x1)) / (x2 - x1);
}

/// Power of 2
///
/// \param  value Value
/// \return 2^n
constexpr uint32_t pow2(uint32_t value) {
  uint32_t result{1u};
  for (uint32_t i{0u}; i < value; ++i)
    result <<= 1u;
  return result;
}

/// Sign
///
/// \tparam T   Type of value
/// \param  value Value
/// \return 0     value == 0
/// \return 1     value > 0
/// \return -1    value < 0
template<typename T>
constexpr int32_t sign(T value) {
  if (value > 0) return 1;
  else if (value < 0) return -1;
  else return 0;
}

/// Make an array with N linearly spaced elements between START and END
///
/// \tparam N     Number of elements
/// \tparam T     Type of values
/// \param  start First value
/// \param  end   Last value
/// \return Linspace array
template<size_t N, typename T>
constexpr auto make_linspace(T start, T end) requires(N >= 1u)
{
  if constexpr (N == 1u) return end;
  else
    return std::invoke(
      [&]<size_t... Is>(std::index_sequence<Is...>) {
        std::array<T, N> retval{start + Is * (end - start) / (N - 1u)...};
        return retval;
      },
      std::make_index_sequence<N>{});
}

/// Digit
///
/// \tparam I             Digit
/// \tparam std::integral Type
/// \param  value         Value
/// \return Digit at position I
template<int I, std::integral T>
requires(I == 1 || I % 10 == 0)
constexpr auto digit(T value) {
  return static_cast<T>((value / I) % 10);
}

/// Ones digit
///
/// \tparam std::integral Type
/// \param  value         Value
/// \return Ones digit
template<std::integral T>
constexpr auto ones_digit(T value) {
  return digit<1>(value);
}

/// Tens digit
///
/// \tparam std::integral Type
/// \param  value         Value
/// \return Tens digit
template<std::integral T>
constexpr auto tens_digit(T value) {
  return digit<10>(value);
}

/// Hundreds digit
///
/// \tparam std::integral Type
/// \param  value         Value
/// \return Hundreds digit
template<std::integral T>
constexpr auto hundreds_digit(T value) {
  return digit<100>(value);
}

}  // namespace ztl
