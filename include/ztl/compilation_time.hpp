// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Compilation time
///
/// \file   ztl/compilation_time.hpp
/// \author Vincent Hamp
/// \date   20/11/2018

#pragma once

#include <cstdint>
#include <ctime>
#include "string.hpp"

namespace ztl {

/// Compilation date and time
struct compilation_time {
  uint8_t day{};
  uint8_t month{};
  uint16_t year{};
  uint8_t hour{};
  uint8_t minute{};
  uint8_t second{};
};

/// Get compilation date and time
///
/// \return Compilation time
constexpr compilation_time make_compilation_time() {
  compilation_time ct{};
  ct.day = atoi(__DATE__ + 3u);
  if (!strcmp(__DATE__, "Jan")) ct.month = 1u;
  else if (!strcmp(__DATE__, "Feb")) ct.month = 2u;
  else if (!strcmp(__DATE__, "Mar")) ct.month = 3u;
  else if (!strcmp(__DATE__, "Apr")) ct.month = 4u;
  else if (!strcmp(__DATE__, "May")) ct.month = 5u;
  else if (!strcmp(__DATE__, "Jun")) ct.month = 6u;
  else if (!strcmp(__DATE__, "Jul")) ct.month = 7u;
  else if (!strcmp(__DATE__, "Aug")) ct.month = 8u;
  else if (!strcmp(__DATE__, "Sep")) ct.month = 9u;
  else if (!strcmp(__DATE__, "Oct")) ct.month = 10u;
  else if (!strcmp(__DATE__, "Nov")) ct.month = 11u;
  else if (!strcmp(__DATE__, "Dec")) ct.month = 12u;
  ct.year = atoi(__DATE__ + 6u);
  ct.hour = atoi(__TIME__);
  ct.minute = atoi(__TIME__ + 3u);
  ct.second = atoi(__TIME__ + 6u);
  return ct;
}

/// Convert compilation time to seconds
///
/// \param  ct  Compilation time to convert
/// \return Compilation time in seconds
constexpr size_t compilation_time2seconds(compilation_time ct) {
  auto count_leap_years{[&ct]() {
    size_t retval{ct.year};
    if (ct.month <= 2u) --retval;
    return retval / 4u - retval / 100u + retval / 400u;
  }};

  auto const is_leap_year{(!(ct.year % 4u) && (ct.year % 100u)) ||
                          !(ct.year % 400u)};

  size_t days{ct.year * 365u + count_leap_years()};

  days += ct.month > 1u ? 31u : 0u;
  days += ct.month > 2u ? is_leap_year ? 29u : 28u : 0u;
  days += ct.month > 3u ? 31u : 0u;
  days += ct.month > 4u ? 30u : 0u;
  days += ct.month > 5u ? 31u : 0u;
  days += ct.month > 6u ? 30u : 0u;
  days += ct.month > 7u ? 31u : 0u;
  days += ct.month > 8u ? 31u : 0u;
  days += ct.month > 9u ? 30u : 0u;
  days += ct.month > 10u ? 31u : 0u;
  days += ct.month > 11u ? 30u : 0u;

  days += ct.day;

  return days * 24u * 3600u + ct.hour * 3600u + ct.minute * 60u + ct.second;
}

/// Default unix epoch (be careful that GCC and Clang both disagree with me and
/// use 01:00:00 as default)
inline constexpr compilation_time default_epoch{
  .day = 1u, .month = 1u, .year = 1970u};

/// Make unix compilation time
///
/// \tparam T     Return type
/// \tparam epoch Epoch to use
/// \return Unix compilation time since epoch
template<typename T = time_t>
constexpr T make_unix_compilation_time(compilation_time epoch = default_epoch) {
  return static_cast<T>(compilation_time2seconds(make_compilation_time()) -
                        compilation_time2seconds(epoch));
}

}  // namespace ztl
