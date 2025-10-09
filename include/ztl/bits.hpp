// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Bits
///
/// \file   ztl/bits.hpp
/// \author Vincent Hamp
/// \date   08/12/2016

#pragma once

#include <concepts>
#include <cstdint>
#include <type_traits>
#include "limits.hpp"

namespace ztl {

/// Checks if a bitmask has only adjacent set bits
///
/// \tparam T Type of bitmask
/// \param t  Bitmask
/// \retval true  Bitmask contiguous
/// \retval false Bitmask not contiguous
template<std::unsigned_integral T>
constexpr auto is_contiguous_bitmask(T const t) {
  return (std::countl_zero(t) + std::countr_zero(t) + std::popcount(t)) ==
         sizeof(T) * 8u;
}

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
template<std::size_t... Bits>
constexpr auto mask{
  static_cast<smallest_unsigned_t<((1u << Bits) | ...)>>(((1u << Bits) | ...))};

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

/// Map value to bitmask
///
/// This function takes a <bitmask, value> pair and maps the value to the set
/// bits of the mask.
///
/// E.g. (0b1101, 0b0101) = 0b1001
///
/// If the value has more bits than the mask, every bit above the masks MSB is
/// ignored.
///
/// \tparam Mask  Bitmask
/// \tparam U     Type of value
/// \param  value Value
/// \return Mapped value
template<std::size_t Mask, std::unsigned_integral U>
constexpr auto map_value_to(U value) {
  using RetType = smallest_unsigned_t<Mask>;
  if (is_contiguous_bitmask(Mask)) // Help with optimisation
    return static_cast<RetType>((value << std::countr_zero(Mask)) & Mask);

  RetType retval{};
  for (auto i{0u}; i < sizeof(RetType) * 8u; ++i)
    // If bit on position is set, shift into retval
    if (Mask & (1u << i)) {
      retval |= static_cast<RetType>((value & 1u) << i);
      value >>= 1u;
    }
  return retval;
}

/// Map value from bitmask - Reverts the map_value_to operation
///
/// \details  Takes a <bitmask, bitfield> pair and re-maps into a value using
///           the bitmask
///
///           E.g. (0b1101, 0b1001) = 0b0101
///
///           Everything above the MSB of the bitmask is ignored.
///
/// \tparam Mask    Bitmask
/// \tparam U       Type of value
/// \param value    Value
/// \return Remapped value
template<std::size_t Mask, std::unsigned_integral U>
constexpr auto map_value_from(U value) {
  using RetType = smallest_unsigned_t<1 << std::popcount(Mask)>;
  if (is_contiguous_bitmask(Mask)) // Help with optimisation
    return static_cast<RetType>((value & Mask) >> std::countr_zero(Mask));

  RetType retval{};
  // If bit on position is set, shift into retval
  for (int i{sizeof(RetType) * 8 - 1}; i >= 0; --i)
    if (Mask & (1u << i)) {
      retval = static_cast<RetType>(retval << 1u);
      retval |= static_cast<RetType>(static_cast<RetType>(value >> i) & 1u);
    }
  return retval;
}

} // namespace ztl
