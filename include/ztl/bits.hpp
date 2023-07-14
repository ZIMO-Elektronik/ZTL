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
/// \tparam T     Type of bitmask
/// \tparam U     Type of value
/// \param  mask  Bitmask
/// \param  value Value
/// \return Value shifted to fit bitmask
template<typename T, typename U>
constexpr uint32_t make_value(T mask, U value) {
  uint32_t retval{};
  for (auto i{0u}; i < sizeof(uint32_t) * 8u; ++i)
    // If bit on position is set, shift into retval
    if (mask & (1u << i)) {
      retval |= (value & 1u) << i;
      value >>= 1u;
    }
  return retval;
}

}  // namespace ztl
