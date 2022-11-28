// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Overload
///
/// \file   ztl/overload.hpp
/// \author Vincent Hamp
/// \date   12/12/2017

#pragma once

namespace ztl {

/// Inherit operator() overloads from Ts...
///
/// \tparam Ts... Types to inherit from
template<typename... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};

template<typename... Ts>
overload(Ts...) -> overload<Ts...>;

}  // namespace ztl
