// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// User defined literals for units
///
/// \file   ztl/units.hpp
/// \author Vincent Hamp
/// \date   06/07/2017

#pragma once

#include <cstdint>

namespace ztl {

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^-6
constexpr float operator"" _u(unsigned long long value) {
  return static_cast<float>(static_cast<double>(value) / 1000000.0);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^-6
constexpr float operator"" _u(long double value) {
  return static_cast<float>(static_cast<double>(value) / 1000000.0);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^-3
constexpr float operator"" _m(unsigned long long value) {
  return static_cast<float>(static_cast<double>(value) / 1000.0);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^-3
constexpr float operator"" _m(long double value) {
  return static_cast<float>(static_cast<double>(value) / 1000.0);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10
constexpr int32_t operator"" _d(unsigned long long value) {
  return static_cast<int32_t>(value * 10);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10
constexpr int32_t operator"" _d(long double value) {
  return static_cast<int32_t>(value * 10);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^3
constexpr int32_t operator"" _k(unsigned long long value) {
  return static_cast<int32_t>(value * 1000);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^3
constexpr int32_t operator"" _k(long double value) {
  return static_cast<int32_t>(value * 1000);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^4
constexpr int32_t operator"" _10k(unsigned long long value) {
  return static_cast<int32_t>(value * 10000);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^4
constexpr int32_t operator"" _10k(long double value) {
  return static_cast<int32_t>(value * 10000);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^6
constexpr int32_t operator"" _M(unsigned long long value) {
  return static_cast<int32_t>(value * 1000000);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^6
constexpr int32_t operator"" _M(long double value) {
  return static_cast<int32_t>(value * 1000000);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^7
constexpr int32_t operator"" _10M(unsigned long long value) {
  return static_cast<int32_t>(value * 10000000);
}

/// SI prefix user defined literal
///
/// \param  value
/// \return value * 10^7
constexpr int32_t operator"" _10M(long double value) {
  return static_cast<int32_t>(value * 10000000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^3
constexpr int32_t operator"" _Hz(unsigned long long frequency) {
  return static_cast<int32_t>(frequency);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^3
constexpr int32_t operator"" _Hz(long double frequency) {
  return static_cast<int32_t>(frequency);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^3
constexpr int32_t operator"" _kHz(unsigned long long frequency) {
  return static_cast<int32_t>(frequency * 1000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^3
constexpr int32_t operator"" _kHz(long double frequency) {
  return static_cast<int32_t>(frequency * 1000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^4
constexpr int32_t operator"" _10kHz(unsigned long long frequency) {
  return static_cast<int32_t>(frequency * 10000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^4
constexpr int32_t operator"" _10kHz(long double frequency) {
  return static_cast<int32_t>(frequency * 10000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^6
constexpr int32_t operator"" _MHz(unsigned long long frequency) {
  return static_cast<int32_t>(frequency * 1000000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^6
constexpr int32_t operator"" _MHz(long double frequency) {
  return static_cast<int32_t>(frequency * 1000000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^7
constexpr int32_t operator"" _10MHz(unsigned long long frequency) {
  return static_cast<int32_t>(frequency * 10000000);
}

/// Frequency user defined literal
///
/// \param  frequency
/// \return frequency * 10^7
constexpr int32_t operator"" _10MHz(long double frequency) {
  return static_cast<int32_t>(frequency * 10000000);
}

/// Time user defined literal
///
/// \param  time
/// \return time * 10^-6
constexpr float operator"" _us(unsigned long long time) {
  return static_cast<float>(static_cast<double>(time) / 1000000.0);
}

/// Time user defined literal
///
/// \param  time
/// \return time * 10^-6
constexpr float operator"" _us(long double time) {
  return static_cast<float>(static_cast<double>(time) / 1000000.0);
}

/// Time user defined literal
///
/// \param  time
/// \return time * 10^-3
constexpr float operator"" _ms(unsigned long long time) {
  return static_cast<float>(static_cast<double>(time) / 1000.0);
}

/// Time user defined literal
///
/// \param  time
/// \return time * 10^-3
constexpr float operator"" _ms(long double time) {
  return static_cast<float>(static_cast<double>(time) / 1000.0);
}

/// Temperature user defined literal
///
/// \param  temp
/// \return temp + 273
constexpr int32_t operator"" _C2K(unsigned long long temp) {
  return static_cast<int32_t>(temp + 273);
}

/// Temperature user defined literal
///
/// \param  temp
/// \return temp + 273.15
constexpr float operator"" _C2K(long double temp) {
  return static_cast<float>(static_cast<double>(temp) + 273.15);
}

}  // namespace ztl
