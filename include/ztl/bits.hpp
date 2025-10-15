// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Bits
///
/// \file   ztl/bits.hpp
/// \author Vincent Hamp
/// \date   08/12/2016

#pragma once

#include <bit>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include "limits.hpp"

namespace ztl {

/// Make mask from bit positions
///
/// \tparam Ts... Type of bit positions
/// \param  bits  Bit positions
/// \return Mask for selected bits
///
/// \deprecated Use mask<Bits...> instead
template<std::unsigned_integral... Ts>
[[deprecated]] constexpr uint32_t make_mask(Ts... bits) {
  return ((1u << bits) | ...);
}

/// Make mask from bit positions
///
/// \tparam Bits  Bit positions
/// \return Mask for selected bits
template<size_t... Bits>
constexpr std::common_type_t<smallest_unsigned_t<((1ull << Bits) | ...)>,
                             uint32_t>
  mask{((1ull << Bits) | ...)};

/// Make value for bitmask
///
/// This function takes a <bitmask, value> pair and maps the value to the set
/// bits of the mask.
///
/// E.g. (0b1101, 0b0101) = 0b1001
///
/// If the value has more bits than the mask, every bit above the masks MSB is
/// ignored.
///
/// \tparam T     Type of bitmask
/// \tparam U     Type of value
/// \param  mask  Bitmask
/// \param  value Value
/// \return Value shifted to fit bitmask
///
/// \deprecated Use map_value_to instead
template<typename T, typename U>
[[deprecated]] constexpr uint32_t make_value(T mask, U value) {
  uint32_t retval{};
  for (auto i{0u}; i < sizeof(uint32_t) * 8u; ++i)
    // If bit on position is set, shift into retval
    if (mask & (1u << i)) {
      retval |= (value & 1u) << i;
      value >>= 1u;
    }
  return retval;
}

/// Count bit runs of adjacent set bits
///
/// \tparam T     Type of bitmask
/// \param  mask  Bitmask
template<std::unsigned_integral T>
constexpr auto runs_count(T mask) noexcept {
  return std::popcount(static_cast<T>(mask & ~(mask << 1u)));
}

namespace detail {

/// Create bit runs from a bitmask
///
/// Creates pairs of start and length of bit runs (groups of adjacent set bits).
/// E.g. 0b1011011u = {0, 2}, {3, 2}, {6, 1}
///
/// \tparam Mask  Bitmask
/// \return Pair of start and length of bit runs
template<auto Mask>
requires(std::unsigned_integral<decltype(Mask)> && Mask != 0u)
consteval auto mask_runs() {
  constexpr auto starts{static_cast<size_t>(Mask & ~(Mask << 1u))};
  std::array<std::pair<size_t, size_t>,
             static_cast<size_t>(std::popcount(starts))>
    retval{};
  auto remaining{starts};
  size_t i{};
  while (remaining) {
    auto const start{static_cast<size_t>(std::countr_zero(remaining))};
    auto const length{static_cast<size_t>(
      std::countr_zero(static_cast<size_t>(~(Mask >> start))))};
    retval[i++] = {start, length};
    remaining = remaining & (remaining - 1u);
  }
  return retval;
}

} // namespace detail

/// Map value to bitmask
///
/// This function takes a <bitmask, value> pair and maps the value to the set
/// bits of the mask.
/// E.g. (0b1101, 0b0101) = 0b1001
/// If the value has more bits than the mask, every bit above the masks MSB is
/// ignored.
///
/// \tparam Mask  Bitmask
/// \tparam R     Return type
/// \tparam T     Type of value
/// \param  value Value
/// \return Mapped value
template<auto Mask, typename R = decltype(Mask), std::unsigned_integral T>
requires(std::unsigned_integral<R> && Mask != 0u)
constexpr auto map_value_to(T value) {
  // Single shift due to single run
  if constexpr (runs_count(Mask) == 1uz)
    return static_cast<R>((value << std::countr_zero(Mask)) & Mask);
  // Multiple shifts
  else {
    constexpr auto runs{detail::mask_runs<Mask>()};
    R retval{};
    for (auto [start, length] : runs) {
      retval |= (value & ((static_cast<R>(1u) << length) - 1u)) << start;
      value >>= length;
    }
    return retval;
  }
}

/// Map value from bitmask - reverts the map_value_to operation
///
/// Takes a <bitmask, bitfield> pair and re-maps into a value using the bitmask.
/// E.g. (0b1101, 0b1001) = 0b0101
/// Everything above the MSB of the bitmask is ignored.
///
/// \tparam Mask  Bitmask
/// \tparam R     Return type
/// \tparam T     Type of value
/// \param  value Value
/// \return Remapped value
template<auto Mask, typename R = decltype(Mask), std::unsigned_integral T>
requires(std::unsigned_integral<R> && Mask != 0u)
constexpr auto map_value_from(T value) {
  // Single shift due to single run
  if constexpr (runs_count(Mask) == 1uz)
    return static_cast<R>((value & Mask) >> std::countr_zero(Mask));
  // Multiple shifts
  else {
    constexpr auto runs{detail::mask_runs<Mask>()};
    R retval{};
    size_t shift{};
    for (auto [start, length] : runs) {
      retval |=
        (static_cast<R>(value >> start) & ((static_cast<R>(1u) << length) - 1u))
        << shift;
      shift += length;
    }
    return retval;
  }
}

} // namespace ztl
