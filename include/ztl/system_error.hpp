// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Embedded friendly version of std::error_code
///
/// \file   ztl/system_error.hpp
/// \author Vincent Hamp
/// \date   27/06/2019

#pragma once

#include <cerrno>
#include <cstring>
#include <optional>
#include <system_error>
#include <utility>

namespace ztl {

/// Since std::error_code forces some ugly inheritence (std::error_category) on
/// us we're better of writing our own without requiring name and message
/// methods.
struct error_code {
  constexpr error_code() = default;
  constexpr error_code(std::errc e) : e_{e} {}
  constexpr operator std::errc() const { return e_; }
  explicit constexpr operator bool() const { return static_cast<bool>(e_); }

private:
  std::errc e_{};
};

/// Print error code
///
/// \param  e   Error
/// \param  fp  Print function
/// \return Number of characters written if successful or a negative value if an
///         error occurred
inline int print_error_code(error_code e, int (*fp)(char const* format, ...)) {
  if (e)
    return fp("%s\n", strerror(std::to_underlying(static_cast<std::errc>(e))));
  else return fp("Success\n");
}

}  // namespace ztl
