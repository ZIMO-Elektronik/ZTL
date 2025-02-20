// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Fail
///
/// \file   ztl/fail.hpp
/// \author Vincent Hamp
/// \date   17/10/2018

#pragma once

#include <type_traits>

namespace ztl {

/// Compile-time fail for use in if constexpr
///
/// \tparam T Obligatory type for delayed instantiation
template<typename T = std::false_type>
void fail() {
  static_assert(T{});
}

} // namespace ztl
