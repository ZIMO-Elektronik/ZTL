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

namespace ztl {

/// Make mask from bit positions
///
/// \tparam Ts... Type of bit positions
/// \param  bits  Bit positions
/// \return Mask for selected bits
template<std::unsigned_integral... Ts>
constexpr uint32_t make_mask(Ts... bits) {
  return ((1u << bits) | ...);
}

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
/// \tparam Packed  Bitmask bits are packed
/// \tparam T     Type of bitmask
/// \tparam U     Type of value
/// \param  mask  Bitmask
/// \param  value Value
/// \return Value shifted to fit bitmask
template<bool Packed = false,
         std::unsigned_integral T,
         std::unsigned_integral U>
constexpr uint32_t make_value(T mask, U value) {
  if (Packed) { // Set bits packet together, faster at runtime than iterating
    return static_cast<uint32_t>((value << std::countr_zero(mask)) & mask);
  }
  uint32_t retval{};
  for (auto i{0u}; i < sizeof(T) * 8u; ++i)
    // If bit on position is set, shift into retval
    if (mask & (1u << i)) {
      retval |= (value & 1u) << i;
      value >>= 1u;
    }
  return retval;
}

/// Extract value for bitmask
///
/// \details  Takes a <bitmask, bitfield> pair and builds a value from the set
///           bits of the mask.
///
///           E.g. (0b1101, 0b1001) = 0b0101
///
///           Everything above the MSB of the bitmask is ignored.
///
/// \tparam Packed  Bitmask bits are packed
/// \tparam T       Type of bitmask
/// \tparam U       Type of value
/// \param mask     Bitmask
/// \param value    Value
/// \return Extracted value fitting bitmask
template<bool Packed = false,
         std::unsigned_integral T,
         std::unsigned_integral U>
constexpr uint32_t extract_value(T mask, U value) {
  if (Packed) { // Set bits packet together, faster at runtime than iterating
    return static_cast<uint32_t>((value & mask) >> std::countr_zero(mask));
  } else {
    uint32_t retval{};
    // If bit on position is set, shift into retval
    for (int i{sizeof(T) * 8 - 1}; i >= 0; --i)
      if (mask & (1u << i)) {
        retval <<= 1;
        retval |= (value >> i) & 1u;
      }
    return retval;
  }
}

} // namespace ztl
