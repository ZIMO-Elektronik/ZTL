// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Implicit wrapper
///
/// \file   ztl/implicit_wrapper.hpp
/// \author Vincent Hamp
/// \date   06/07/2019

#pragma once

#include <type_traits>
#include <utility>

namespace ztl {

/// Wrapper with implicit conversions to underlying type
///
/// \tparam T Type to wrap
template<typename T, typename = void>
struct implicit_wrapper {
  using value_type = T;

  explicit constexpr implicit_wrapper() = default;

  explicit constexpr implicit_wrapper(value_type const& value)
    : _value(value) {}

  explicit constexpr implicit_wrapper(value_type&& value)
    : _value(std::move(value)) {}

  constexpr implicit_wrapper& operator=(value_type const& value) {
    _value = value;
    return *this;
  }

  constexpr implicit_wrapper& operator=(value_type&& value) {
    _value = std::move(value);
    return *this;
  }

  constexpr value_type& value() & { return _value; }
  constexpr value_type const& value() const& { return _value; }
  constexpr value_type&& value() && { return std::move(_value); }
  constexpr value_type const&& value() const&& { return std::move(_value); }

  constexpr operator value_type&() & { return value(); }
  constexpr operator value_type const&() const& { return value(); }
  constexpr operator value_type&&() && { return std::move(value()); }
  constexpr operator value_type const&&() const&& { return std::move(value()); }

private:
  value_type _value{};
};

}  // namespace ztl
