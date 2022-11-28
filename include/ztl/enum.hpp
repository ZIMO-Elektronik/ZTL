// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Enum flags
///
/// \file   ztl/enum.hpp
/// \author Vincent Hamp
/// \date   05/06/2018

#pragma once

#include <utility>

#define ZTL_MAKE_ENUM_CLASS_FLAGS(E)                                           \
  constexpr E operator~(E rhs) {                                               \
    return static_cast<E>(~std::to_underlying(rhs));                           \
  }                                                                            \
  constexpr E operator&(E lhs, E rhs) {                                        \
    return static_cast<E>(std::to_underlying(lhs) & std::to_underlying(rhs));  \
  }                                                                            \
  constexpr E operator|(E lhs, E rhs) {                                        \
    return static_cast<E>(std::to_underlying(lhs) | std::to_underlying(rhs));  \
  }                                                                            \
  constexpr E operator^(E lhs, E rhs) {                                        \
    return static_cast<E>(std::to_underlying(lhs) ^ std::to_underlying(rhs));  \
  }                                                                            \
  constexpr E operator<<(E lhs, E rhs) {                                       \
    return static_cast<E>(std::to_underlying(lhs) << std::to_underlying(rhs)); \
  }                                                                            \
  constexpr E operator>>(E lhs, E rhs) {                                       \
    return static_cast<E>(std::to_underlying(lhs) >> std::to_underlying(rhs)); \
  }                                                                            \
  constexpr E& operator&=(E& lhs, E rhs) { return lhs = lhs & rhs; }           \
  constexpr E& operator|=(E& lhs, E rhs) { return lhs = lhs | rhs; }           \
  constexpr E& operator^=(E& lhs, E rhs) { return lhs = lhs ^ rhs; }           \
  constexpr E& operator<<=(E& lhs, E rhs) { return lhs = lhs << rhs; }         \
  constexpr E& operator>>=(E& lhs, E rhs) { return lhs = lhs >> rhs; }         \
  constexpr bool operator!(E rhs) { return !std::to_underlying(rhs); }         \
  constexpr std::underlying_type_t<E> operator+(E rhs) {                       \
    return std::to_underlying(rhs);                                            \
  }                                                                            \
  constexpr std::underlying_type_t<E> operator-(E rhs) {                       \
    return -std::to_underlying(rhs);                                           \
  }
