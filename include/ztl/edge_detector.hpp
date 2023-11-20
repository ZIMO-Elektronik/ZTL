// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Edge detector
///
/// \file   ztl/edge_detector.hpp
/// \author Samuel Sillaber
/// \date   28/07/2021

#pragma once

namespace ztl {

/// Detect rising and falling edges
struct edge_detector {
  enum transition { none, rising, falling };

  constexpr edge_detector() = default;
  explicit constexpr edge_detector(bool value) : _value{value} {}

  [[nodiscard]] constexpr transition operator()(bool value) {
    if (value == _value) return none;
    return (_value = value) ? rising : falling;
  }

private:
  bool _value{false};
};

}  // namespace ztl