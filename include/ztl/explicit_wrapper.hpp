// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Explicit wrapper
///
/// \file   ztl/explicit_wrapper.hpp
/// \author Vincent Hamp
/// \date   08/05/2019

#pragma once

#include <type_traits>
#include <utility>

namespace ztl {

/// Wrapper without any implicit conversion
///
/// \tparam T Type to wrap
template<typename T, typename = void>
struct explicit_wrapper {
  using value_type = T;

  explicit constexpr explicit_wrapper() = default;

  explicit constexpr explicit_wrapper(value_type const& value)
    : _value(value) {}

  explicit constexpr explicit_wrapper(value_type&& value)
    : _value(std::move(value)) {}

  constexpr value_type& value() & { return _value; }
  constexpr value_type const& value() const& { return _value; }
  constexpr value_type&& value() && { return std::move(_value); }
  constexpr value_type const&& value() const&& { return std::move(_value); }

  explicit constexpr operator value_type&() { return value(); }
  explicit constexpr operator value_type const&() const& { return value(); }
  explicit constexpr operator value_type&&() && { return std::move(value()); }
  explicit constexpr operator value_type const&&() const&& {
    return std::move(value());
  }

  explicit constexpr operator bool() const { return value(); }

private:
  value_type _value{};
};

}  // namespace ztl
