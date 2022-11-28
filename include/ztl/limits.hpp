// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Limits
///
/// \file   ztl/limits.hpp
/// \author Vincent Hamp
/// \date   05/09/2018

#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace ztl {

/// Smallest signed type which fits [Min, Max]
///
/// \tparam Min Lowest value
/// \tparam Max Largest value
template<int64_t Min, int64_t Max>
using smallest_signed_t = std::conditional_t<
  Min >= std::numeric_limits<int8_t>::min() &&
    Max <= std::numeric_limits<int8_t>::max(),
  int8_t,
  std::conditional_t<
    Min >= std::numeric_limits<int16_t>::min() &&
      Max <= std::numeric_limits<int16_t>::max(),
    int16_t,
    std::conditional_t<Min >= std::numeric_limits<int32_t>::min() &&
                         Max <= std::numeric_limits<int32_t>::max(),
                       int32_t,
                       int64_t>>>;

/// Smallest unsigned type which fits [0, Max]
///
/// \tparam Max Largest value
template<uint64_t Max>
using smallest_unsigned_t = std::conditional_t<
  Max <= std::numeric_limits<uint8_t>::max(),
  uint8_t,
  std::conditional_t<
    Max <= std::numeric_limits<uint16_t>::max(),
    uint16_t,
    std::conditional_t<Max <= std::numeric_limits<uint32_t>::max(),
                       uint32_t,
                       uint64_t>>>;

}  // namespace ztl
